#pragma once
#include"Controller.hpp"
#include"Algorithm.hpp"
class ThreadTesting
{
	/*ThreadTesting instantiates object of template class Controller and is used like testing class for different quantity of threads*/
public:
	void test2Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS);//All algoritms are paralelled for 2 threads

	void test4Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS);//All algoritms are paralelled for 4 threads

	void test8Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS);//All algoritms are paralelled for  threads

}; 
