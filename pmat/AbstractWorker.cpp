#include "pch.h"
#include "AbstractWorker.h"
#include "WorkManagerProdMatrix.h"


/**
 * @brief Notifies this worker that a work ended
*/
void AbstractWorker::notifyEndOfWork()
{
	_endOfWork = true;
}

/**
 * @brief Performs tasks until the work ends;
*/
void AbstractWorker::startTask() const
{
	_manager->dispatchNextTask(_identifier);
	while (!_endOfWork) {
		this->performTask();
		_manager->dispatchNextTask(_identifier);
	}
}

