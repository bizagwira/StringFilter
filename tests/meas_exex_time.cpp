#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <map>
#include <vector>
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

class Node;

class Node: public std::enable_shared_from_this<Node> {
	public:
		Node(const char& value='/'):
		_value(value){}
		~Node(){}
	
		char value()const {return _value;}

		std::string prefix() const {
			return this->_prefix;
		}
	    
		void setParent(std::shared_ptr<Node> parent){
			this->_parent = parent;
			this->_prefix = this->_parent->prefix() + this->_value;
		}
		
		std::shared_ptr<Node>&
		insert(const char value){
			std::map<char, std::shared_ptr<Node>>::iterator iter = this->_children.find(value);

			if (iter == this->_children.end()) {
				iter = this->_children.emplace(std::make_pair(value, std::shared_ptr<Node>(new Node(value)))).first;
			} 
			
			std::shared_ptr<Node>& child = iter->second;
			child->setParent(shared_from_this());

			return child;
		}	
		
		std::shared_ptr<Node>&
		search(const char value){
			std::map<char, std::shared_ptr<Node>>::iterator iter = this->_children.find(value);
			return iter->second;
		}
		
		void increment() {
			this->_counter += 1;
		}
		
		void insert(const std::string& entry) {
			std::shared_ptr<Node> parent = shared_from_this();
			for(const char& c : entry) {
				parent = parent->insert(c);
			}
			parent->increment();
		}
		
		void appendResult (std::vector<std::string>& results) {
			if (this->_children.size() == 0 || this->_counter > 0) {
				results.push_back(this->_prefix);
			}
		}

		void collect (std::vector<std::string>& results) {
			this->appendResult(results);
			for(const auto& entry : this->_children) {
				entry.second->collect(results);
			}
		}
		
		void find(const std::string& entry, std::vector<std::string>& results) {
			std::shared_ptr<Node> parent = shared_from_this();
			for(const char& c : entry) {
				parent = parent->search(c);
				if (parent == nullptr) break;
			}

			results.clear();
			if (parent != nullptr) {
				parent->collect(results);
			}
		}

	private:
		char _value;
		long _counter = 0;
		std::string _prefix = "";
		std::shared_ptr<Node> _parent;
		std::map<char, std::shared_ptr<Node>> _children;
};

int main(int argc, const char *argv[]){ 

	std::ifstream fs("words.txt");
	std::vector<std::string> database;
    std::copy(std::istream_iterator<std::string>(fs),
         std::istream_iterator<std::string>(),
         back_inserter(database));

	auto root  = std::make_shared<Node>();
	
	for(const std::string& entry : database) {
		root->insert(entry);
	}
	
	std::vector<std::string> results;

	std::cout << "#################################" << std::endl;

	auto t1 = high_resolution_clock::now();
	root->find("AST", results);
	auto t2 = high_resolution_clock::now();

    // Getting number of milliseconds as an integer. 
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

	for (const std::string& x: results){
		std::cout << x << std::endl;
	}

    // Getting number of milliseconds as a double.
    duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "[" << __LINE__ << "]\tDuration: "  << ms_int.count() << "ms\n";
    std::cout << "[" << __LINE__ << "]\tDuration: " << ms_double.count() << "ms\n";

	return 0;
}