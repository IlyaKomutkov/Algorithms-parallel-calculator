#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <algorithm>
#include <string>
#include <thread>


template <size_t N, class T>
class Controller {
	/* This class is using for parallel calculations */
	std::mutex mutex1, mutex2;
	std::condition_variable done;
	std::deque<T> que;
	std::deque<std::string> PATHS;

	bool Finished[N];

	//Initializing bool variables
	void reset() {
		for (bool& i : Finished) {
			i = false;
		}
	}
	//Make calculations in thread that got as parametr of function
	void thread_task(size_t id){
		while (true)
		{
			std::unique_lock<std::mutex> lock(mutex1);
			if (que.empty()) {
				std::unique_lock<std::mutex> lock(mutex2);
				Finished[id] = true;
				done.notify_all(); //Unblocks all threads currently waiting for this condition
				lock.unlock();
				return;
			}
			int i = 0;
			auto job = std::move(que.front()); //Elements are taken in turn(one by one) till deque is not empty 
			que.pop_front();

			std::string fileName = PATHS.front();
			PATHS.pop_front();

			lock.unlock();

			job->start(fileName);

			// Method "start" starts calculations of i-th element of deque
			// std::cout << "algorithm" << std::endl;
			// std::cout << "Thread id: "<< std::this_thread::get_id() << std::endl;
			// std::cout << fileName << std::endl << std::endl;
			// i++;

		}
	}

public:
	//Add object in queue
	void push(const T job, const std::string path) {
		std::unique_lock<std::mutex> lock(mutex1);
		que.emplace_back(std::move(job));
		PATHS.emplace_back(path);
	}
	//Implementation of the algorithm
	void start() {
		reset();
		for (size_t i = 0; i < N; i++) {
			std::thread worker([this, i]() {
				thread_task(i); 
			});
			worker.detach();
		}
	}
	//Controlling the end of process
	void wait_finished() {
		std::unique_lock<std::mutex> lock(mutex2);
		done.wait(lock, [this] {
			return std::all_of(Finished, Finished + N - 1, [](bool e) {return e; });
		});
	}
};


