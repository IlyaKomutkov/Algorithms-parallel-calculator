#include "ThreadTesting.hpp"

#include 

//All algoritms are paralelled for 2 threads
void ThreadTesting::test2Threads(std::vector<Algorithm*> algorithms,\
									std::vector<std::string> PATHS){
	Controller<2, Algorithm*> pool;

	for (int i = 0; i < algorithms.size(); i++){
		pool.push(algorithms[i], PATHS[i]);
	}
	pool.start();
	pool.wait_finished();

}

//All algoritms are paralelled for 4 threads
void ThreadTesting::test4Threads(std::vector<Algorithm*> algorithms,\
									std::vector<std::string>PATHS) {
	Controller<4, Algorithm*> pool;

	for (int i = 0; i < algorithms.size(); i++){
		pool.push(algorithms[i], PATHS[i]);
	}
	pool.start();
	pool.wait_finished();

}

//All algoritms are paralelled for  threads
void ThreadTesting::test8Threads(std::vector<Algorithm*> algorithms,\
								std::vector<std::string>PATHS) {
	Controller<8, Algorithm*> pool;

	for (int i = 0; i < algorithms.size(); i++) {
		pool.push(algorithms[i], PATHS[i]);
	}
	pool.start();
	pool.wait_finished();

	}
