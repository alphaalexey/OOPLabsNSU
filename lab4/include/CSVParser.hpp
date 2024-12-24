#pragma once

#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// Exception class to handle parsing errors with line and column information
class CSVParserException : public std::runtime_error {
public:
    CSVParserException(const std::string &msg, size_t line, size_t column)
        : std::runtime_error(msg), line_(line), column_(column) {}

    size_t line() const { return line_; }
    size_t column() const { return column_; }

private:
    size_t line_;
    size_t column_;
};

// CSVParser template class
template <typename... Types> class CSVParser {
public:
    CSVParser(std::istream &file, size_t skip_lines = 0, char row_delim = '\n',
              char col_delim = ',', char escape_char = '"')
        : file_(file), skip_lines_(skip_lines), row_delim_(row_delim),
          col_delim_(col_delim), escape_char_(escape_char) {
        // Skip initial lines if necessary
        for (size_t i = 0; i < skip_lines_; i++) {
            file_.ignore(std::numeric_limits<std::streamsize>::max(),
                         row_delim_);
        }
    }

    // Iterator class definition
    class iterator {
    public:
        iterator() : parser_(nullptr), is_end_(true) {}

        iterator(CSVParser *parser)
            : parser_(parser), is_end_(false),
              line_number_(parser->skip_lines_) {
            ++(*this); // Load the first value
        }

        std::tuple<Types...> operator*() const { return current_value_; }

        std::tuple<Types...> *operator->() { return &current_value_; }

        iterator &operator++() {
            if (is_end_)
                return *this;

            std::string line;
            if (!std::getline(parser_->file_, line, parser_->row_delim_)) {
                is_end_ = true;
                parser_ = nullptr;
                return *this;
            }
            ++line_number_;
            try {
                parse_line(line);
            } catch (const CSVParserException &) {
                throw; // Rethrow with line and column info
            } catch (const std::exception &e) {
                throw CSVParserException(e.what(), line_number_, 0);
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const iterator &other) const {
            return (is_end_ == other.is_end_) && (parser_ == other.parser_);
        }

        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

    private:
        void parse_line(const std::string &line) {
            std::vector<std::string> fields;
            parse_fields(line, fields);

            if (fields.size() != sizeof...(Types)) {
                throw CSVParserException("Incorrect number of fields",
                                         line_number_, 0);
            }

            assign_tuple(fields, current_value_,
                         std::index_sequence_for<Types...>{});
        }

        void parse_fields(const std::string &line,
                          std::vector<std::string> &fields) {
            size_t pos = 0, len = line.length(), column = 1;
            while (pos < len) {
                std::string field;
                if (line[pos] == parser_->escape_char_) {
                    ++pos;
                    bool escape_closed = false;
                    while (pos < len) {
                        if (line[pos] == parser_->escape_char_) {
                            if (pos + 1 < len &&
                                line[pos + 1] == parser_->escape_char_) {
                                field += parser_->escape_char_;
                                pos += 2;
                            } else {
                                ++pos;
                                escape_closed = true;
                                break;
                            }
                        } else {
                            field += line[pos++];
                        }
                    }
                    if (!escape_closed) {
                        throw CSVParserException("Unclosed escape character",
                                                 line_number_, column);
                    }
                    while (pos < len && line[pos] != parser_->col_delim_) {
                        if (!isspace(line[pos])) {
                            throw CSVParserException(
                                "Unexpected character after closing escape "
                                "character",
                                line_number_, column);
                        }
                        ++pos;
                    }
                } else {
                    while (pos < len && line[pos] != parser_->col_delim_) {
                        field += line[pos++];
                    }
                }
                fields.push_back(field);
                if (pos < len && line[pos] == parser_->col_delim_) {
                    ++pos;
                    ++column;
                } else {
                    break;
                }
            }
        }

        template <std::size_t... Is>
        void assign_tuple(const std::vector<std::string> &fields,
                          std::tuple<Types...> &tup,
                          std::index_sequence<Is...>) {
            try {
                ((assign_field(std::get<Is>(tup), fields[Is], line_number_,
                               Is + 1)),
                 ...);
            } catch (const CSVParserException &) {
                throw;
            } catch (const std::exception &e) {
                throw CSVParserException(e.what(), line_number_, 0);
            }
        }

        template <typename T>
        void assign_field(T &field, const std::string &str, size_t line_number,
                          size_t column_number) {
            std::istringstream ss(str);
            ss >> field;
            if (ss.fail() || !ss.eof()) {
                throw CSVParserException("Failed to parse field '" + str + "'",
                                         line_number, column_number);
            }
        }

        void assign_field(std::string &field, const std::string &str, size_t,
                          size_t) {
            field = str;
        }

        CSVParser *parser_;
        std::tuple<Types...> current_value_;
        bool is_end_;
        size_t line_number_;
    };

    iterator begin() { return iterator(this); }

    iterator end() { return iterator(); }

private:
    std::istream &file_;
    size_t skip_lines_;
    char row_delim_;
    char col_delim_;
    char escape_char_;
};
