#include "node.hpp"


std::mutex Node::_glock;

Node::Node(const char value):
_value(value){

}


std::shared_ptr<Node>
Node::insert(const char value){

	std::shared_ptr<Node> child;

	auto itr = std::find_if(this->_children.cbegin(), this->_children.cend(), NodeComparator(value));

	if (itr != this->_children.cend()) {
	    child = *itr;
	}
	else {
		child = std::shared_ptr<Node>(new Node(value));
	}

	this->addChild(child);
	return child ;
}

void 
Node::push_back (std::vector<std::string>& results) {
	if (this->_children.size() == 0 || this->_counter > 0) {
		std::lock_guard<std::mutex> guard(Node::_glock);
		results.push_back(this->_prefix);
	}
}

void 
Node::collect (std::vector<std::string>& results){
	this->push_back(results);
	for(const auto& entry : this->_children) {
		entry->collect(results);
	}
}


std::shared_ptr<Node> 
Node::search(const char& c) {
	std::lock_guard<std::mutex> guard(Node::_glock);
	if (this->_children.size() == 0) return nullptr;

	auto node = std::find_if(this->_children.cbegin(), this->_children.cend(), NodeComparator(c));
	return *node;
}
	