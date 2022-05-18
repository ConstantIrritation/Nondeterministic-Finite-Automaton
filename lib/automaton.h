#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

struct Node {
    bool terminal = false;
    std::unordered_map<char, std::vector<size_t>> transitions;
};

struct Edge {
    size_t from = 0;
    size_t to = 0;
    Edge(size_t from, size_t to) : from(from), to(to) {}
};

class Automaton {
public:

    Automaton(const std::string& s);
    bool CheckIfContained(const std::string& word);

private:
    std::vector<Node> autom;
    std::stack<Edge> current_pos;
    size_t start = 0;
    bool is_correct = true;

private:

    void AddEdge(size_t node_from, char with, size_t node_to);

    void Add();
    void Mult();
    void Kleene();
    void Letter(char c);
};
