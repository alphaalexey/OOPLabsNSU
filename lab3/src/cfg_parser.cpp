#include "cfg_parser.h"

#include <fstream>
#include <sstream>

ConfigParser::ConfigParser(const std::string &filename) : filename(filename) {}

std::vector<std::unique_ptr<IConverter>> ConfigParser::parseConverters(
    const std::vector<std::string> &inputFiles) {

    std::ifstream file(filename);
    if (!file)
        throw ConfigError();

    std::vector<std::unique_ptr<IConverter>> converters;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "mute") {
            int start, end;
            iss >> start >> end;
            converters.push_back(std::make_unique<MuteConverter>(start, end));
        } else if (cmd == "mix") {
            int streamIdx, pos;
            iss >> streamIdx >> pos;
            if (streamIdx < 1 || streamIdx > inputFiles.size()) {
                throw ConfigError();
            }
            converters.push_back(std::make_unique<MixConverter>(
                inputFiles[streamIdx - 1], pos));
        } else if (cmd == "echo") {
            int delay, decay;
            iss >> delay >> decay;
            converters.push_back(std::make_unique<EchoConverter>(delay, decay));
        } else {
            throw ConfigError();
        }
    }
    return converters;
}
