#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include<string>
#include<map>

template <size_t N, class T>
class Controller
{
	/*This class is using for parallel calculations*/
	std::mutex mutex1, mutex2;
	std::condition_variable done;
	std::deque<T> que;
	std::deque<std::string>PATHS;
	bool Finished[N];
	void reset()//Initializing bool variables
	{
		for (bool& i : Finished)
		{
			i = false;
		}
	}
	void thread_task(size_t id)//Make calculations in thread that got as parametr of function
	{
		while (true)
		{
			std::unique_lock<std::mutex> lock(mutex1);
			if (que.empty())
			{
				std::unique_lock<std::mutex> lock(mutex2);
				Finished[id] = true;
				done.notify_all();//Unblocks all threads currently waiting for this condition
				return;
			}
			int i = 0;
			auto job = std::move(que.front());//Elements are taken in turn(one by one) till deque is not empty 
			que.pop_front();
			lock.unlock();
			const char firstSymbol = PATHS[0].front();//For message in concole
			PATHS.pop_front();
			//std::string algName, resultPATH;
			(firstSymbol == 'R')
			{
				algName = "RK Integrator Algorithm ";
				resultPATH = "RK/results/TwoBodyOdeSolution.csv";
			}
			else
			{
				algName = "KMeans Algorithm";
				resultPATH = "KMEans/results/ThreeBodyOdeSolution.csv";
			}
			job->start("PIDR");//Method "start" starts calculations of i-th element of deque
			//std::cout << algName<<std::endl 
			//<<"Thread id: "<< std::this_thread::get_id() << std::endl
			//<<resultPATH<<std::endl<<std::endl;
			//i++;

		}

	}
public:
	void push(const T job, const std::string path)//Adding object in queue
	{

		std::unique_lock<std::mutex> lock(mutex1);
		que.emplace_back(std::move(job));
		PATHS.emplace_back(path);
	}
	void start()//Implementation of the algorithm
	{
		reset();
		for (size_t i = 0; i < N; i++)
		{
			std::thread worker([this, i]() {
				thread_task(i); 
			});
			worker.detach();
		}
	}
	void wait_finished()//Controlling the end of process
	{
		std::unique_lock<std::mutex> lock(mutex2);
		done.wait(lock, [this]
		{
			return std::all_of(Finished, Finished + N - 1, [](bool e) {return e; });
		});
	}
};


