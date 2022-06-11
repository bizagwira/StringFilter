#include "node.hpp"
#include "tree.hpp"
#include <fstream>


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

void 
Tree::split(std::vector<std::string> origin, std::vector<std::string> splited[], const size_t& number) {
	size_t n = origin.size()/number + 1;
	// each iteration of this loop process the next set of `n` elements
	// and store it in a vector at k'th index in `vec`
	for (size_t k = 0; k < number; ++k) {
		// get range for the next set of `n` elements
		auto start_itr = std::next(origin.cbegin(), k*n);
		auto end_itr = std::next(origin.cbegin(), k*n + n);

		// allocate memory for the sub-vector
		splited[k].resize(n);

		// code to handle the last sub-vector as it might
		// contain fewer elements
		if (k*n + n > origin.size()) {
			end_itr = origin.cend();
			splited[k].resize(origin.size() - k*n);
		}

		// copy elements from the input range to the sub-vector
		std::copy(start_itr, end_itr, splited[k].begin());
	}	
}


