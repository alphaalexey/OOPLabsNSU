#pragma once

#include <cstdint>
#include <string>
#include <vector>

class WavFile {
public:
    WavFile(const std::string &filename);
    void read();
    void write(const std::string &filename);
    const std::vector<int16_t> &getSamples() { return samples; }
    void setSamples(std::vector<int16_t> &&samples) { this->samples = samples; }
    size_t getSampleCount() const { return samples.size(); }
    uint32_t getSampleRate() const { return sampleRate; }

    class UnsupportedFormatException : public std::exception {
        const char *what() const noexcept override {
            return "Unsupported WAV file format.";
        }
    };

    static const uint32_t defaultSampleRate = 44100;

private:
    std::string filename;
    std::vector<int16_t> samples;
    uint32_t sampleRate;
    void parseHeader(std::ifstream &file);
};
