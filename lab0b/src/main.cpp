#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <map>
#include <set>

int main(int argc, char *argv[]) {
    using namespace std;

    try {
        locale loc("ru_RU.UTF-8");
        locale::global(loc);
    } catch (runtime_error &e) {
        cout << "Failed to set locale: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    if (argc != 3) {
        cout << "Usage: " << argv[0] << " input.txt output.csv" << endl;
        return EXIT_FAILURE;
    }

    wifstream fin(argv[1]);
    if (!fin) {
        cout << "Cannot open input file: " << argv[1] << endl;
        return EXIT_FAILURE;
    }

    wofstream fout(argv[2]);
    if (!fout) {
        cout << "Cannot open output file: " << argv[2] << endl;
        return EXIT_FAILURE;
    }

    long word_count = 0;
    map<wstring, long> word_map;

    wstring line;
    while (getline(fin, line)) {
        wstring word;
        for (auto it = line.begin(); it != line.end(); it++) {
            if (iswalnum(*it)) {
                word += *it;
            } else if (!word.empty()) {
                word_map[word]++;
                word_count++;
                word.clear();
            }
        }
        if (!word.empty()) {
            word_map[word]++;
            word_count++;
        }
    }

    set<pair<long, wstring>> temp;
    for (auto it = word_map.begin(); it != word_map.end(); it++) {
        temp.insert({it->second, it->first});
    }
    for (auto it = temp.rbegin(); it != temp.rend(); it++) {
        fout << it->second << "," << it->first << "," << setprecision(3)
             << static_cast<double>(it->first) * 100 / word_count << endl;
    }

    return EXIT_SUCCESS;
}
