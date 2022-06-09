#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "node.hpp"
#include "tree.hpp"
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>

namespace po = boost::program_options;




int main(int argc, const char *argv[]){

	std::string filepath, pattern;

	try {
		po::options_description desc("Allowed options");
		desc.add_options()
		("help", "Submit the file path data")
		("filepath", po::value<std::string>(&filepath), "Set the file path data")
		("pattern", po::value<std::string>(&pattern), "Enter the pattern");


		po::variables_map vm;

		// parse regular options
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << "\n";
			return 0;
		}

		if (vm.count("pattern")) {
			std::cout << "pattern: " << pattern << std::endl;
		} 
		else {
			std::cout << "The pattern was not set.\n";
		}

		if (vm.count("filepath")) {
			std::cout << "filepath: " << filepath << std::endl;
		} 
		else {
			std::cout << "The filepath was not set.\n";
		}

	}
	catch(std::exception& e) {
		std::cerr << "error: " << e.what() << "\n";
		return 1;
	}


	std::shared_ptr<Tree> tree = std::make_shared<Tree>();

	// Read the input file 
	std::ifstream infile(filepath);
	std::string entry;
	while (std::getline(infile, entry)) {
		tree->add(entry);
	}
	std::cout << "[" << __LINE__ << "]\t###################### Finish build the tree" << std::endl;
	// Declare the results container vector
	std::vector<std::string> results;
	results.reserve(1000);
	// Grep the given word from the tree data
	tree->filter(pattern, results);
	std::cout << "[" << __LINE__ << "]\t###################### End filtering" << std::endl;
	// Show the results
	for(const std::string& entry : results) {
		std::cout << "[" << __LINE__ << "]\t" << entry << std::endl;
	}

	return 0;
}