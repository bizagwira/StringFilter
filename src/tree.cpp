#include "node.hpp"
#include "tree.hpp"


// std::atomic<bool> Tree::busy(true);

Tree::Tree(const char& value):
Node(value){

}

void 
Tree::add(const std::string& entry) {
	std::shared_ptr<Node> parent = shared_from_this();
	for(const char& c : entry) {
		parent = parent->insert(c);
	}
	parent->increment();
}


void 
Tree::find(const std::string& entry) {
	std::shared_ptr<Node> parent = shared_from_this();
	for(const char& c : entry) {
		parent = parent->search(c);
		if (parent == nullptr) break;
	}

	this->_results.clear();
	if (parent != nullptr) {
		parent->collect(this->_results);
	}
}

void 
Tree::filter(const std::string& pattern, std::vector<std::string>& results) {
	// Start a new search
	results.clear();

	std::shared_ptr<Node> matchNode = shared_from_this();
	for(const char& c : pattern) {
		if (matchNode == nullptr) break;
		matchNode = matchNode->search(c);
	}

	if (matchNode != nullptr) {
		matchNode->push_back(results);
		std::vector<std::thread> thread_list{};

		for(const auto& child : matchNode->children()) {
			thread_list.push_back( std::thread{Worker(results), child} );
		}

		for(auto& t: thread_list) { t.join(); }
	}
}