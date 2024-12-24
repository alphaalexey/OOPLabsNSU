#include "wav_file.h"

#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct WavHeader {
    union {
        char groupID[4];
        uint32_t groupIDi;
    };
    int32_t size;
    union {
        char riffType[4];
        uint32_t riffTypei;
    };
};

struct WavChunkBase {
    union {
        char chunkID[4];
        uint32_t chunkIDi;
    };
    int32_t chunkSize;
};

struct WavFormat : WavChunkBase {
    int16_t wFormatTag;
    uint16_t wChannels;
    uint32_t dwSamplesPerSec;
    uint32_t dwAvgBytesPerSec;
    uint16_t wBlockAlign;
    uint16_t wBitsPerSample;
};

WavFile::WavFile(const std::string &filename)
    : filename(filename), sampleRate(defaultSampleRate) {}

void WavFile::read() {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening WAV file.");
    }

    parseHeader(file);

    WavChunkBase dataBase;

    // Skip all chunks except "data"
    while (true) {
        file.read(reinterpret_cast<char *>(&dataBase), sizeof(dataBase));
        if (!file) {
            throw std::runtime_error("Error reading WAV data chunk from file.");
        }

        // "data" = 0x61746164
        if (dataBase.chunkIDi == 0x61746164) {
            break;
        }
    }

    if (dataBase.chunkSize % sizeof(int16_t) != 0) {
        throw std::runtime_error("Error corrupted WAV file.");
    }

    // Reading samples as 16-bit signed integers
    samples.resize(dataBase.chunkSize / sizeof(int16_t));
    file.read(reinterpret_cast<char *>(samples.data()), dataBase.chunkSize);
    if (!file) {
        throw std::runtime_error("Error reading WAV data from file.");
    }
}

void WavFile::parseHeader(std::ifstream &file) {
    WavHeader header;
    file.read(reinterpret_cast<char *>(&header), sizeof(header));
    if (!file) {
        throw std::runtime_error("Error reading WAV header from file.");
    }

    // Validate header
    // "RIFF" = 0x46464952, "WAVE" = 0x45564157
    if (header.groupIDi != 0x46464952 || header.riffTypei != 0x45564157) {
        throw UnsupportedFormatException();
    }

    WavFormat format;
    file.read(reinterpret_cast<char *>(&format), sizeof(format));
    if (!file) {
        throw std::runtime_error("Error reading WAV format from file.");
    }

    // Validate format
    // "fmt " = 0x20746d66
    if (format.chunkIDi != 0x20746d66 || format.wFormatTag != 1 ||
        format.wChannels != 1 || format.dwSamplesPerSec != defaultSampleRate ||
        format.wBitsPerSample != 16) {
        throw UnsupportedFormatException();
    }

    sampleRate = format.dwSamplesPerSec;
}

void WavFile::write(const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error creating WAV file.");
    }

    uint32_t dataSize = samples.size() * sizeof(int16_t);

    WavFormat format;
    format.chunkIDi = 0x20746d66;
    format.chunkSize = 16;
    format.wFormatTag = 1;
    format.wChannels = 1;
    format.dwSamplesPerSec = sampleRate * format.wChannels;
    format.dwAvgBytesPerSec = sampleRate * format.wChannels * sizeof(int16_t);
    format.wBlockAlign = format.wChannels * sizeof(int16_t);
    format.wBitsPerSample = sizeof(int16_t) * 8;

    WavChunkBase dataBase;
    dataBase.chunkIDi = 0x61746164;
    dataBase.chunkSize = dataSize;

    WavHeader header;
    header.groupIDi = 0x46464952;
    header.size = sizeof(header.riffType) + sizeof(WavFormat) + sizeof(WavChunkBase) + dataSize;
    header.riffTypei = 0x45564157;

    file.write(reinterpret_cast<char *>(&header), sizeof(header));
    file.write(reinterpret_cast<char *>(&format), sizeof(format));
    file.write(reinterpret_cast<char *>(&dataBase), sizeof(dataBase));
    file.write(reinterpret_cast<char *>(samples.data()), dataSize);
}
