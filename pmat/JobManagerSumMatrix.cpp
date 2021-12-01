#include "pch.h"
#include "JobManagerSumMatrix.h"
#include "WorkerSumMatrix.h"


void JobManagerSumMatrix::setTask(unsigned identifier)
{
	if (_lastRow < _operandA->getRowSize()) {
		const auto worker = dynamic_cast<WorkerSumMatrix*> (_workers[identifier]);
		worker->setRow(_lastRow);
		_lastRow++;
	}
	else
		_workers[identifier]->endTask();

}

JobManagerSumMatrix::JobManagerSumMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result,
	unsigned nWorkers)
{
	_operandA = &operandA;
	_operandB = &operandB;
	_result = &result;
	_nWorkers = nWorkers;
	_workers.clear();
	for (unsigned i = 0; i < _nWorkers; ++i)
		_workers.push_back(new WorkerSumMatrix(i, (*this)));

}

JobManagerSumMatrix::~JobManagerSumMatrix()
{
	for (unsigned i = 0; i < _nWorkers; ++i)
		delete dynamic_cast<WorkerSumMatrix*> (_workers[i]);
}
