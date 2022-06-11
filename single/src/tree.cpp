#include "node.hpp"
#include "tree.hpp"
#include <fstream>


// std::atomic<bool> Tree::busy(true);

Tree::Tree(const char& value):
Node(value){
}

void 
Tree::upload(const std::string filepath){
    std::ifstream fs(filepath);
    std::vector<std::string> database;
    std::copy(std::istream_iterator<std::string>(fs),
         std::istream_iterator<std::string>(),
         back_inserter(database));
    
    this->upload(database);
}

void 
Tree::upload(const std::vector<std::string> database){
    for(const std::string& entry : database) {
        this->insert(entry);
    }
}

void 
Tree::insert(const std::string& entry) {
	std::shared_ptr<Node> parent = shared_from_this();
	for(const char& c : entry) {
		parent = parent->insert(c);
	}
	parent->increment();
}

void 
Tree::find(const std::string& entry, std::vector<std::string>& results) {
	std::shared_ptr<Node> parent = shared_from_this();
	for(const char& c : entry) {
		parent = parent->search(c);
		
		if (parent == nullptr) break;
	}

	if (parent != nullptr) {
		parent->collect(results, entry);
	}
}

