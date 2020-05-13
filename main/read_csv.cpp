#include "read_csv.hpp"


std::vector<std::vector<std::string>> CSVReader::getFullData(){
	std::ifstream file(fileName);
	std::vector<std::vector<std::string>> dataList;
	std::string line = "";

	while (getline(file, line))
	{	
		
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	file.close();
	return dataList;
}


std::vector<std::string> CSVReader::getStr(){
	std::ifstream file(fileName);
	std::vector<std::string> dataStr;
	std::string line = "";
	getline(file, line);
	boost::algorithm::split(dataStr, line, boost::is_any_of(delimeter));
	file.close();
	return dataStr;
}

