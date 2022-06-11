
#ifndef TREE_H
#define TREE_H
#include <string>
#include <thread>

#define WORKER_NUMBER   4

class Node;

class Tree: public Node {

    public:
        Tree(const char& value='/');

        void insert(const std::string& entry);

        void upload(const std::string filepath);

        void upload(const std::vector<std::string> database);

        void find(const std::string& s, std::vector<std::string>& results);

        static void split(std::vector<std::string> origin, std::vector<std::string> splited[], const size_t& number=WORKER_NUMBER);

};


struct Worker {
    std::string _pattern;
    std::vector<std::string>& _results;


    Worker(std::vector<std::string>& res, const std::string pattern): _results(res), _pattern(pattern){ }

    void operator()(std::shared_ptr<Tree> tree) {
        tree->find(this->_pattern, this->_results);
    }
};

#endif /* TREE_H */