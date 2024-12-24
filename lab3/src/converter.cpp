#include "converter.h"

#include "wav_file.h"

MuteConverter::MuteConverter(int startSec, int endSec)
    : start(startSec), end(endSec) {}

void MuteConverter::apply(std::vector<int16_t> &samples) {
    size_t startSample = start * WavFile::defaultSampleRate;
    size_t endSample = end * WavFile::defaultSampleRate;

    if (startSample > samples.size())
        return;

    if (endSample > samples.size())
        endSample = samples.size();

    for (size_t i = startSample; i < endSample; i++) {
        samples[i] = 0;
    }
}

MixConverter::MixConverter(const std::string &otherFile,
                           int insertPos)
    : insertPosition(insertPos) {
        WavFile file(otherFile);
        file.read();
        mixSamples = std::move(file.getSamples());
    }

void MixConverter::apply(std::vector<int16_t> &samples) {
    size_t insertSample = insertPosition * WavFile::defaultSampleRate;
    for (size_t i = 0;
         i < mixSamples.size() && (insertSample + i) < samples.size(); i++) {
        samples[insertSample + i] =
            (samples[insertSample + i] + mixSamples[i]) / 2;
    }
}

EchoConverter::EchoConverter(int delayMs, int decay)
    : delay(delayMs), decay(decay) {}

void EchoConverter::apply(std::vector<int16_t> &samples) {
    size_t delaySamples = (delay * WavFile::defaultSampleRate) / 1000;
    for (size_t i = delaySamples; i < samples.size(); i++) {
        samples[i] += samples[i - delaySamples] * decay / 100;
    }
}
