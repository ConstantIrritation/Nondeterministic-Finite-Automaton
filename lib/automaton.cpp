#include "automaton.h"

Automaton::Automaton(const std::string& s) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '+') {
            if (current_pos.size() < 2) {
                std::cout << "Error + \n";
                is_correct = false;
                break;
            }
            Add();
        } else if (s[i] == '.') {
            if (current_pos.size() < 2) {
                std::cout << "Error .\n";
                is_correct = false;
                break;
            }
            Mult();
        } else if (s[i] == '*') {
            if (current_pos.size() < 1) {
                std::cout << "Error * \n";
                is_correct = false;
                break;
            }
            Kleene();
        } else if (s[i] == ' ') {
            continue;
        } else {
            Letter(s[i]);
        }
    }
    if (current_pos.size() != 1) {
        std::cout << "Error balance\n";
        is_correct = false;
    }
    start = current_pos.top().from;
}

void Automaton::AddEdge(size_t node_from, char with, size_t node_to) {
    auto ans = autom[node_from].transitions.find(with);
    if (ans == autom[node_from].transitions.end()) {
        autom[node_from].transitions.insert({with, std::vector<size_t>(1, node_to)});
    } else {
        std::vector<size_t> way_to = ans->second;
        way_to.push_back(node_to);
        autom[node_from].transitions.erase(with);
        autom[node_from].transitions.insert({with, way_to});
    }
}

void Automaton::Add() {
    Edge second = current_pos.top();
    current_pos.pop();
    Edge first = current_pos.top();
    current_pos.pop();

    autom.emplace_back(Node());
    autom.back().transitions.insert({'1', {first.from, second.from}});

    autom.emplace_back(Node());
    autom[first.to].terminal  = false;
    autom[second.to].terminal = false;
    autom.back().terminal     = true;

    AddEdge(first.to,  '1', autom.size() - 1);
    AddEdge(second.to, '1', autom.size() - 1);

    current_pos.push(Edge(autom.size() - 2, autom.size() - 1));
}

void Automaton::Mult() {
    Edge second = current_pos.top();
    current_pos.pop();
    Edge first = current_pos.top();
    current_pos.pop();

    autom[first.to].terminal = false;

    AddEdge(first.to, '1', second.from);

    current_pos.push(Edge(first.from, second.to));
}

void Automaton::Kleene() {
    Edge edge = current_pos.top();
    current_pos.pop();

    autom.emplace_back(Node());
    autom[edge.to].terminal = false;
    autom.back().terminal   = true;

    AddEdge(edge.to,          '1', autom.size() - 1);
    AddEdge(autom.size() - 1, '1', edge.from);

    current_pos.push(Edge(autom.size() - 1, autom.size() - 1));
}

void Automaton::Letter(char c) {
    autom.emplace_back(Node());
    autom.back().transitions.insert({c, std::vector<size_t>(1, autom.size())});
    autom.emplace_back(Node());
    autom.back().terminal = true;

    current_pos.push(Edge(autom.size() - 2, autom.size() - 1));
}

bool Automaton::CheckIfContained(const std::string& word) {
    if (!is_correct) {
        std::cout << "Bad structure\n";
        return false;
    }

    std::queue<std::pair<size_t, size_t>> dfs;
    dfs.push(std::make_pair(start, 0));

    std::vector<std::unordered_set<size_t>> no_loops(autom.size());
    no_loops[start].insert(0);

    while (!dfs.empty()) {
        auto value = dfs.front();
        dfs.pop();

        if (value.second >= word.size() && 
            autom[value.first].terminal == true) return true;

        if (value.second < word.size()) {
            auto check = autom[value.first].transitions.find(word[value.second]);
            if (check != autom[value.first].transitions.end()) {
                for (auto i : check->second) {
                    if (no_loops[i].find(value.second + 1) == no_loops[i].end()) {
                        no_loops[i].insert(value.second + 1);
                        dfs.push(std::make_pair(i, value.second + 1));
                    }
                }
            }
        }

        auto check = autom[value.first].transitions.find('1');
        if (check != autom[value.first].transitions.end()) {
            for (auto i : check->second) {
                if (no_loops[i].find(value.second) == no_loops[i].end()) {
                    no_loops[i].insert(value.second);
                    dfs.push(std::make_pair(i, value.second));
                }
            }
        }
    }
    return false;
}
