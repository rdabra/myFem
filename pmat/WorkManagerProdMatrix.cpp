#include "pch.h"
#include "WorkManagerProdMatrix.h"
#include "WorkerProdMatrix.h"
#include <thread>


void WorkManagerProdMatrix::setTask(unsigned identifier)
{
	if (_lastRowA < _operandA->getRowSize()) {
		const auto worker = dynamic_cast<WorkerProdMatrix*>(_workers[identifier]);
		worker->setRowColumn(_lastRowA, _lastColumnB);
		if (_lastColumnB < _operandB->getColumnSize() - 1) {
			_lastColumnB++;
		}
		else {
			_lastRowA++;
			_lastColumnB = 0;
		}
	}
	else
		_workers[identifier]->notifyEndOfWork();
}

void WorkManagerProdMatrix::setResultValue(double value, unsigned rowIndex, unsigned columnIndex)
{
	std::lock_guard<std::mutex> guard{_mutexSetValue};
	_result->setValue(value, rowIndex, columnIndex);
}

WorkManagerProdMatrix::~WorkManagerProdMatrix()
{
	for (unsigned i = 0; i < _nWorkers; ++i)
		delete dynamic_cast<WorkerProdMatrix*>(_workers[i]);
}

WorkManagerProdMatrix::WorkManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result,
                                             unsigned nWorkers) : _nWorkers(nWorkers), _result(&result),
                                                                  _operandA(&operandA),
                                                                  _operandB(&operandB)
{
	_workers.clear();
	for (unsigned i = 0; i < _nWorkers; ++i)
		_workers.push_back(new WorkerProdMatrix(i, (*this)));
}
