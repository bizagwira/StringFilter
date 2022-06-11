#ifndef NODE_H
#define NODE_H
#include <stdint.h>
#include <vector>
#include <memory>
#include <iostream>
#include <mutex>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class Node;


class Node: public std::enable_shared_from_this<Node> { 
	public:
		Node(const char value);

		~Node(){};

		std::ostream& operator<<(std::ostream& out) {
			out << this->_value << '/' << this->_children.size();
			return out;
		}

		Node& operator=(const Node& other) {
		  if(this == &other) return *this; 
		  this->_value = other._value;
		  this->_parent = other._parent;
		  this->_children = other._children;
		  return *this;
		}

		Node& operator=(Node&& other) {
		  if(this == &other) return *this; 
		  this->_value = other._value;
		  this->_parent = other._parent;
		  this->_children = other._children;
		  return *this;
		}

		bool operator==(const Node& other){
			std::cout << "[" << __LINE__ << "]\t" << this->_value <<"\t" << other._value << std::endl;
		    return this->_value == other._value;
		}

		// Node(Node&& other) {
		// 	this->_value = other._value;
		// 	this->_parent = other._parent;
		// 	this->_children = other._children;
		// 	other._parent = nullptr;
		// 	other._children.clear();
		// }

		char value() const {
			return this->_value;
		}
    
	    void setParent(std::shared_ptr<Node> parent){
	        this->_parent = parent;
	        this->_prefix = this->_parent->prefix() + this->_value;
	    }

		void addChild(std::shared_ptr<Node> child){
			this->_children.push_back(child);
			child->setParent(shared_from_this());
		}

		std::vector<std::shared_ptr<Node>> children() const{
			return this->_children;
		}

		std::string prefix() const {
			return this->_prefix;
		}

		void increment() {
			this->_counter += 1;
		}

		void push_back (std::vector<std::string>& results);

		void collect (std::vector<std::string>& results, const std::string& pattern);

		void collect (std::vector<std::string>& results);

		std::shared_ptr<Node> search(const char& x);

		virtual std::shared_ptr<Node> insert(const char value);

		static std::mutex _glock;
	private:
		char _value;
		std::shared_ptr<Node> _parent;
		std::vector<std::shared_ptr<Node>> _children;
		std::vector<std::string> _data;
		std::string _prefix = "";
		long _counter = 0;	// Number of complet words where this node is the last character
		

	friend struct NodeComparator;
};

struct NodeComparator {
    const char &_value;
    NodeComparator(const char& value) : _value(value) {}
    bool operator()(const std::shared_ptr<Node> &second) {
        return _value == second->_value;
    }
};


#endif /* NODE_H */