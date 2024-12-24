#pragma once

#include <exception>
#include <memory>
#include <string>
#include <vector>

#include "converter.h"

class ConfigParser {
public:
    explicit ConfigParser(const std::string &filename);
    std::vector<std::unique_ptr<IConverter>>
    parseConverters(const std::vector<std::string> &inputSamples);

    class ConfigError : public std::exception {
        const char *what() const noexcept override {
            return "Configuration parsing error.";
        }
    };

private:
    std::string filename;
};
