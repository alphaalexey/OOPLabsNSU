#pragma once

#include <cstdint>
#include <string>
#include <vector>

class IConverter {
public:
    virtual ~IConverter() = default;
    virtual void apply(std::vector<int16_t> &samples) = 0;
};

class MuteConverter : public IConverter {
    int start, end;

public:
    MuteConverter(int startSec, int endSec);
    void apply(std::vector<int16_t> &samples) override;
};

class MixConverter : public IConverter {
    std::vector<int16_t> mixSamples;
    int insertPosition;

public:
    MixConverter(const std::string &otherFile, int insertPos);
    void apply(std::vector<int16_t> &samples) override;
};

class EchoConverter : public IConverter {
    int delay, decay;

public:
    EchoConverter(int delayMs, int decay);
    void apply(std::vector<int16_t> &samples) override;
};
