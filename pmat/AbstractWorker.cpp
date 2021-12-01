#include "pch.h"
#include "AbstractWorker.h"
#include "JobManagerProdMatrix.h"


void AbstractWorker::endTask()
{
	_endTask = true;
}

void AbstractWorker::startTask() const
{
	_manager->notifyIdleness(_identifier);
	while (!_endTask) {
		this->makeTask();
		_manager->notifyIdleness(_identifier);
	}
}

