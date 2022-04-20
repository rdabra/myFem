#include "pch.h"
#include "WorkerSumMatrix.h"
#include "WorkManagerSumMatrix.h"


void WorkerSumMatrix::setRow(unsigned rowIndex)
{
	_row = rowIndex;
	_endOfWork = false;
}


void WorkerSumMatrix::performTask() const
{
	const auto man = dynamic_cast<WorkManagerSumMatrix*>(_manager);
	for (unsigned j = 0; j < man->_operandA->getColumnSize(); ++j)
		man->setResultValue((*man->_operandA)(_row, j) + (*man->_operandB)(_row, j), _row, j);
}
