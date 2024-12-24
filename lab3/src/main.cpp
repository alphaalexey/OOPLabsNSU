#include <iostream>

#include "processor.h"

int main(int argc, char *argv[]) {
    if (argc < 2 || std::string(argv[1]) == "-h") {
        std::cout << "Usage: sound_processor -c <config.txt> <output.wav> "
                     "<input1.wav> [<input2.wav> ...]"
                  << std::endl;
        std::cout << "Available converters:" << std::endl;
        std::cout << "    mute <start> <end>" << std::endl;
        std::cout << "    mix <stream> <pos>" << std::endl;
        std::cout << "    echo <delay> <decay>" << std::endl;
        return EXIT_SUCCESS;
    }

    try {
        SoundProcessor processor(argv[2], argv[3], {argv + 4, argv + argc});
        processor.process();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
