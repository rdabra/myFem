#include "pch.h"
#include "WorkerProdMatrix.h"
#include "JobManagerProdMatrix.h"


void WorkerProdMatrix::setRowColumn(unsigned rowA, unsigned columnB)
{
	_rowA = rowA;
	_columnB = columnB;
	_endTask = false;
}

void WorkerProdMatrix::makeTask() const
{
	double sum{putils::ZERO};
	for (unsigned j = 0; j < _manager->_operandA->getColumnSize(); ++j)
		sum += (*_manager->_operandA)(_rowA, j) * (*_manager->_operandB)(j, _columnB);
	_manager->_result->setValue(sum, _rowA, _columnB);
}
