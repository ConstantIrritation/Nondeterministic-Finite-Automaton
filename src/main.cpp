#include <iostream>
#include <string>

#include "automaton.h"

int main() {
    std::string reg_exp, word;
    std::getline(std::cin, reg_exp);
    std::cin >> word;
    Automaton automaton(reg_exp);
    size_t max_suff_len = 0;

    for (size_t i = 0; i < word.size(); ++i) {

        auto substring = word.substr(i, word.size());

        if (automaton.CheckIfContained(substring)) {
            max_suff_len = substring.size();
            break;
        }
    }

    if (max_suff_len > 0) {

        std::cout << max_suff_len << '\n';
    } else {
        std::cout << "INF\n";
    }

    return 0;
}
