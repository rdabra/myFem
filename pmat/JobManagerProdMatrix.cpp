#include "pch.h"
#include "JobManagerProdMatrix.h"


void JobManagerProdMatrix::setTask(unsigned identifier)
{
	if (_lastRowA < _operandA->getRowSize()) {
		const auto worker = dynamic_cast<WorkerProdMatrix*> (_workers[identifier]);
		worker->setRowColumn(_lastRowA, _lastColumnB);
		if (_lastColumnB < _operandB->getColumnSize() - 1) {
			_lastColumnB++;
		}
		else {
			_lastRowA++;
			_lastColumnB = 0;
		}
	} else
		_workers[identifier]->endTask();
}

JobManagerProdMatrix::~JobManagerProdMatrix()
{

	for (unsigned i = 0; i < _nWorkers; ++i) 
		delete dynamic_cast<WorkerProdMatrix*> (_workers[i]);
}

JobManagerProdMatrix::JobManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result,
                                           unsigned nWorkers)
{
	_operandA = &operandA;
	_operandB = &operandB;
	_result = &result;
	_nWorkers = nWorkers;
	_workers.clear();
	for (unsigned i = 0; i < _nWorkers; ++i) 
		_workers.push_back(new WorkerProdMatrix(i, (*this)));
}

