#include "pch.h"
#include "JobManagerProdMatrix.h"


void JobManagerProdMatrix::startJob(const unsigned nWorkers)
{
	_tasks.clear();
	for (unsigned i = 0; i < nWorkers; ++i)
		_tasks.emplace_back(i, (*this));

	std::vector<std::thread> workers;
	for (auto& task : _tasks)
		workers.emplace_back(&JobTaskProdMatrix::startTask, &task);
	for (auto& worker : workers)
		worker.join();
	workers.clear();
}

void JobManagerProdMatrix::notifyIdleness(unsigned identifier)
{
	std::lock_guard<std::mutex> guard{_mutex};
	if (_lastRowA < _operandA.getRowSize()) {
		_tasks[identifier].setRowColumn(_lastRowA, _lastColumnB);
		if (_lastColumnB < _operandB.getColumnSize() - 1) {
			_lastColumnB++;
		}
		else {
			_lastRowA++;
			_lastColumnB = 0;
		}
	}
	else {
		_tasks[identifier].endTask();
	}
}
