#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>
#include "node.hpp"
#include "tree.hpp"

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


	std::ifstream fs(filepath);

	std::vector<std::string> dataArray;
	
	std::copy(std::istream_iterator<std::string>(fs), std::istream_iterator<std::string>(), back_inserter(dataArray));

	// create an array of vectors to store the sub-vectors
	std::vector<std::string> vec[WORKER_NUMBER];
	Tree::split(dataArray, vec);

	std::vector<std::shared_ptr<Tree>> trees(WORKER_NUMBER);
	size_t counter = 0;
	for (auto& p : trees) {
		p = std::make_shared<Tree>();
	}

	for (int i = 0; i < WORKER_NUMBER; i++) {
		trees[i]->upload(vec[i]);
	}

	std::vector<std::string> results;
	std::vector<std::thread> thread_list{};

	for(const auto& tree :trees) {
		thread_list.push_back( std::thread{Worker(results, pattern), tree} );
	}
	auto t1 = high_resolution_clock::now();
	for(auto& t: thread_list) { t.join(); }

	auto t2 = high_resolution_clock::now();
	// Getting number of milliseconds as an integer. 
	auto ms_int = duration_cast<milliseconds>(t2 - t1);

	// Show the results
	for(const std::string& entry : results) {
		std::cout << "[" << __LINE__ << "]\t" << entry << std::endl;
	}

	// Getting number of milliseconds as a double.
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << ms_int.count() << "ms\n";
	std::cout << ms_double.count() << "ms\n";
	return 0;
}