
#ifndef TREE_H
#define TREE_H
#include <string>
#include <thread>

class Node;

class Tree: public Node {

    public:
        Tree(const char& value='/');

        void add(const std::string& entry);

        void find(const std::string& s);

        void filter(const std::string& s, std::vector<std::string>& results);

        std::vector<std::string>& results() {
            return _results;
        }

    private:
        std::vector<std::string> _results;
};


struct Worker {
    std::vector<std::string>& _results;

    Worker(std::vector<std::string>& res): _results(res){ }

    void operator()(std::shared_ptr<Node> node) {
        node->collect(this->_results);
    }
};

#endif /* TREE_H */