#include"threadtesting.h"



	void ThreadTesting::test2Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS)//All algoritms are paralelled for 2 threads
	{
		Controller<2, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
	void ThreadTesting::test4Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS)//All algoritms are paralelled for 4 threads
	{
		Controller<4, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
	void ThreadTesting::test8Threads(std::vector<Algorithm*> algorithms, std::vector<std::string>PATHS)//All algoritms are paralelled for  threads
	{
		Controller<8, Algorithm*>pool;

		for (int i = 0; i < algorithms.size(); i++)
		{
			pool.push(algorithms[i], PATHS[i]);
		}
		pool.start();
		pool.wait_finished();

	}
