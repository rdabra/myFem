#include "pch.h"
#include "AbstractMatrixTriangular.h"


void AbstractMatrixTriangular::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	validateIndex(rowIndex, columnIndex);

	_matrix[this->getVectorIndex(rowIndex, columnIndex)] = value;
}


MatrixSquare AbstractMatrixTriangular::asMatrixSquare() const
{
	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	}

	return resp;
}


double AbstractMatrixTriangular::frobeniusNorm() const
{
	return sqrt(this->dotProduct((*this)));
}


MatrixSquare AbstractMatrixTriangular::getSwappedByRows(const unsigned& rowIndexA, const unsigned& rowIndexB) const
{
	this->validateIndex(rowIndexA, 0);
	this->validateIndex(rowIndexB, 0);

	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		unsigned k = i;
		if (i == rowIndexA) k = rowIndexB;
		else if (i == rowIndexB) k = rowIndexA;
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(k, j), i, j);
	}

	return resp;
}

void AbstractMatrixTriangular::swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB,
                                               const unsigned& startColumn, const unsigned& endColumn)
{
	if (startColumn > endColumn)
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::swapRowElements(rowIndexA, rowIndexB, startColumn, endColumn);
}

MatrixSquare AbstractMatrixTriangular::getSwappedByColumns(const unsigned& columnIndexA,
                                                           const unsigned& columnIndexB) const
{
	this->validateIndex(0, columnIndexA);
	this->validateIndex(0, columnIndexB);

	MatrixSquare resp(this->getSize());
	for (unsigned j = 0; j < this->getSize(); ++j) {
		unsigned k = j;
		if (j == columnIndexA) k = columnIndexB;
		else if (j == columnIndexB) k = columnIndexA;
		for (unsigned i = 0; i < this->getSize(); ++i)
			resp.setValue((*this)(i, k), i, j);
	}

	return resp;
}

void AbstractMatrixTriangular::swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                                  const unsigned& startRow, const unsigned& endRow)
{
	if (startRow > endRow)
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::swapColumnElements(columnIndexA, columnIndexB, startRow, endRow);
}


double AbstractMatrixTriangular::determinant()
{
	double resp = putils::ONE;

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*this)(i, i);

	return resp;
}
