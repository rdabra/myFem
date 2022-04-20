#include "pch.h"
#include "AbstractWorkManager.h"

/**
 * @brief Creates a group of workers and starts the tasks of each one
*/
void AbstractWorkManager::startWork() const
{
	std::vector<std::thread> group;
	for (auto worker : _workers)
		group.emplace_back(&AbstractWorker::startTask, worker); // Creates a thread in a "member function" scheme and inserts it at the end
	for (auto& worker : group)
		worker.join(); // Wait for everybody to finish
	group.clear(); // 
}

/**
 * @brief Starts a work and measure its duration 
 * @return Duration in milliseconds
*/
double AbstractWorkManager::measureWorkTime() const
{
	const auto t1 = std::chrono::high_resolution_clock::now();
	this->startWork();
	const auto t2 = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> duration = t2 - t1;
	return duration.count();
}


/**
 * @brief Dispatches to a worker the next task, if available
 * @param identifier Number that uniquely identifies a worker
*/
void AbstractWorkManager::dispatchNextTask(unsigned identifier)
{
	std::lock_guard<std::mutex> guard{_mutexDispatchTask}; // Avoids concurrency from now on until the end of the function
	this->setTask(identifier);
}
