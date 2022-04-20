#pragma once

#include <mutex>
#include "Matrix.h"
#include "AbstractWorker.h"

/**
 * @brief Manages a work to be done by a group of workers
 * @detail A work is a set of equal tasks
*/
class AbstractWorkManager
{
private:
	std::mutex _mutexDispatchTask;

protected:
	std::vector<AbstractWorker*> _workers;
	virtual void setTask(unsigned identifier) = 0;

public:
	virtual ~AbstractWorkManager() = default;

	void startWork() const;
	double measureWorkTime() const;
	void dispatchNextTask(unsigned identifier);

};
