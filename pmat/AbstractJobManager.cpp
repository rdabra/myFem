#include "pch.h"
#include "AbstractJobManager.h"

void AbstractJobManager::startJob() const
{
	std::vector<std::thread> workers;
	for (auto task : _workers)
		workers.emplace_back(&AbstractWorker::startTask, task);
	for (auto& worker : workers)
		worker.join();
	workers.clear();
}

double AbstractJobManager::timeJob() const
{
	const auto t1 = std::chrono::high_resolution_clock::now();
	this->startJob();
	const auto t2 = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> duration = t2 - t1;
	return duration.count();
}


void AbstractJobManager::notifyIdleness(unsigned identifier)
{
	std::lock_guard<std::mutex> guard{_mutex};
	this->setTask(identifier);
}
