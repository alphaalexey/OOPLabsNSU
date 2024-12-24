#include <fstream>
#include <iostream>
#include <tuple>

#include "CSVParser.hpp"

template <class Ch, class Tr, class Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr> &os, const Tuple &t,
                      std::index_sequence<Is...>) {
    ((os << (Is ? ",\t" : "") << std::get<Is>(t)), ...);
}

template <class Ch, class Tr, class... Args>
auto &operator<<(std::basic_ostream<Ch, Tr> &os, const std::tuple<Args...> &t) {
    os << '(';
    print_tuple_impl(os, t, std::index_sequence_for<Args...>{});
    return os << ')';
}

int main(int argc, char *argv[]) {
    std::tuple t{1, 2, 3, 6, 4, 5};
    std::cout << t << std::endl << std::endl;

    std::string filename = "test.csv";
    if (argc == 2) {
        filename = argv[1];
    }

    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file 'test.csv'" << std::endl;
            return EXIT_FAILURE;
        }

        // file, skip_lines, row_delim, col_delim, escape_char
        CSVParser<std::string, int, int, int, float, float, float, float, int> parser(file, 1, '\n', ';', '\'');
        for (const auto &rs : parser) {
            std::cout << rs << std::endl;
        }
    } catch (const CSVParserException &e) {
        std::cerr << "Parsing error at line " << e.line() << ", column "
                  << e.column() << ": " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
