#include "processor.h"

#include "cfg_parser.h"
#include "wav_file.h"

SoundProcessor::SoundProcessor(const std::string &configFile,
                               const std::string &outputFile,
                               const std::vector<std::string> &inputFiles)

    : configFile(configFile), outputFile(outputFile), inputFiles(inputFiles) {}

void SoundProcessor::process() {
    ConfigParser parser(configFile);
    auto converters = parser.parseConverters(inputFiles);

    WavFile inputWav(inputFiles[0]);
    inputWav.read();

    auto outputSamples = inputWav.getSamples();
    for (const auto &converter : converters) {
        converter->apply(outputSamples);
    }

    WavFile outputWav(outputFile);
    outputWav.setSamples(std::move(outputSamples));
    outputWav.write(outputFile);
}
