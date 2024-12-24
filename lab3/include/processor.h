#pragma once

#include <string>
#include <vector>

class SoundProcessor {
public:
    SoundProcessor(const std::string &configFile, const std::string &outputFile,
                   const std::vector<std::string> &inputFiles);

    void process();

private:
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
};
