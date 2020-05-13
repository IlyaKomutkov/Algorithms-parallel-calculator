#pragma once

#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <sstream>

// Boost is used for parsing .csv 
#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"


class CSVReader{
	std::string fileName;
	std::string delimeter;
public:
	CSVReader(std::string filename, std::string delm = ","):
		fileName(filename), delimeter(delm){}

	std::vector<std::vector<std::string>> getFullData();// get data like separated lines
	std::vector<std::string> getStr();					// get 1 line separated values
};	
