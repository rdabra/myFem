#pragma once

#include <mutex>
#include <thread>
#include "Matrix.h"
#include "AbstractWorker.h"
#include "utils.h"

class AbstractJobManager
{
private:
	std::mutex _mutex;

protected:
	std::vector<AbstractWorker*> _workers;
	virtual void setTask(unsigned identifier) = 0;

public:
	virtual ~AbstractJobManager() = default;

	void startJob() const;
	double timeJob() const;
	void notifyIdleness(unsigned identifier);

};
