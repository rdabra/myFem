#include "pch.h"
#include "WorkManagerSumMatrix.h"
#include "WorkerSumMatrix.h"



void WorkManagerSumMatrix::setTask(unsigned identifier)
{
	if (_lastRow < _operandA->getRowSize()) {
		const auto worker = dynamic_cast<WorkerSumMatrix*> (_workers[identifier]);
		worker->setRow(_lastRow);
		_lastRow++;
	}
	else
		_workers[identifier]->notifyEndOfWork();

}

WorkManagerSumMatrix::WorkManagerSumMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result,
	unsigned nWorkers) : _nWorkers(nWorkers), _operandA(&operandA), _operandB(&operandB), _result(&result)
{
	_workers.clear();
	for (unsigned i = 0; i < _nWorkers; ++i)
		_workers.push_back(new WorkerSumMatrix(i, (*this)));

}

WorkManagerSumMatrix::~WorkManagerSumMatrix()
{
	for (unsigned i = 0; i < _nWorkers; ++i)
		delete dynamic_cast<WorkerSumMatrix*> (_workers[i]);
}

void WorkManagerSumMatrix::setResultValue(double value, unsigned rowIndex, unsigned columnIndex)
{
	std::lock_guard<std::mutex> guard{ _mutexSetValue }; // Avoids concurrency from now on until the end of function
	_result->setValue(value, rowIndex, columnIndex);
}
