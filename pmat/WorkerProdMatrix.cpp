#include "pch.h"
#include "WorkerProdMatrix.h"


void WorkerProdMatrix::setRowColumn(unsigned rowA, unsigned columnB)
{
	_rowA = rowA;
	_columnB = columnB;
	_endTask = false;
}

void WorkerProdMatrix::makeTask() const
{
	const auto man = dynamic_cast<JobManagerProdMatrix*> (_manager);
	double sum{ putils::ZERO };
	for (unsigned j = 0; j < man->_operandA->getColumnSize(); ++j)
		sum += (*man->_operandA)(_rowA, j) * (*man->_operandB)(j, _columnB);
	man->_result->setValue(sum, _rowA, _columnB);
}
