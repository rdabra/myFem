#include "pch.h"
#include "JobTaskProdMatrix.h"

#include <iostream>

#include "JobManagerProdMatrix.h"


void JobTaskProdMatrix::setRowColumn(unsigned rowA, unsigned columnB)
{
	_rowA = rowA;
	_columnB = columnB;
	_endTask = false;
}

void JobTaskProdMatrix::startTask() const
{
	_manager.notifyIdleness(_identifier);
	while (!_endTask) {
		double sum{putils::ZERO};
		for (unsigned j = 0; j < _manager._operandA.getColumnSize(); ++j)
			sum += _manager._operandA(_rowA, j) * _manager._operandB(j, _columnB);
		_manager._result.setValue(sum, _rowA, _columnB);
		_manager.notifyIdleness(_identifier);
	}
}

void JobTaskProdMatrix::endTask()
{
	_endTask = true;
}
