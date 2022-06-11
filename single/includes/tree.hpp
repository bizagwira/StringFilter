
#ifndef TREE_H
#define TREE_H
#include <string>
#include <thread>

class Node;

class Tree: public Node {

    public:
        Tree(const char& value='/');

        void insert(const std::string& entry);

        void find(const std::string& s, std::vector<std::string>& results);

        void upload(const std::string filepath);

        void upload(const std::vector<std::string> database);

    private:
};

#endif /* TREE_H */