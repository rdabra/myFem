#include "pch.h"
#include "WorkerSumMatrix.h"
#include "JobManagerSumMatrix.h"


void WorkerSumMatrix::setRow(unsigned row)
{
	_row = row;
	_endTask = false;
}


void WorkerSumMatrix::makeTask() const
{
	const auto man = dynamic_cast<JobManagerSumMatrix*>(_manager);
	for (unsigned j = 0; j < man->_operandA->getColumnSize(); ++j)
		man->_result->setValue((*man->_operandA)(_row, j) + (*man->_operandB)(_row, j), _row, j);
}
