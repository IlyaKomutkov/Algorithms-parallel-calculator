#pragma once
#include"Controller.hpp"
#include"Algorithm.hpp"


struct ThreadTesting
{
	/*ThreadTesting instantiates object of template class Controller and is used like testing class for different quantity of threads*/
	
	void test2Threads(std::vector<Algorithm*> algorithms,std::vector<std::string>PATHS)//All algoritms are paralelled for 2 threads
	{
		Controller<2, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
	void test4Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS)//All algoritms are paralelled for 4 threads
	{
		Controller<4, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
	void test8Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS)//All algoritms are paralelled for 8 threads
	{
		Controller<8, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
};