#include "pch.h"
#include "AbstractMatrixTriangular.h"


/**
 * @brief Sets a value for an element
 * @details Indexes of constant zero elements are not allowed to be set
 * @param value Value to be set
 * @param rowIndex Row index
 * @param columnIndex Column index
 * @exception std::logic_error Indexes out of bounds 
*/
void AbstractMatrixTriangular::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	validateIndex(rowIndex, columnIndex);

	_matrix[this->getVectorIndex(rowIndex, columnIndex)] = value;
}


/**
 * @brief Creates a copy of this matrix as a square matrix
 * @return A copy of this matrix as a square matrix
*/
MatrixSquare AbstractMatrixTriangular::toMatrixSquare() const
{
	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	}

	return resp;
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

void AbstractMatrixTriangular::partialSwapRows(const unsigned& rowIndexA, const unsigned& rowIndexB,
                                               const unsigned& startColumn, const unsigned& endColumn)
{
	if (startColumn > endColumn)
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::partialSwapRows(rowIndexA, rowIndexB, startColumn, endColumn);
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

void AbstractMatrixTriangular::partialSwapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                                  const unsigned& startRow, const unsigned& endRow)
{
	if (startRow > endRow)
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::partialSwapColumns(columnIndexA, columnIndexB, startRow, endRow);
}


double AbstractMatrixTriangular::determinant()
{
	double resp = putils::ONE;

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*this)(i, i);

	return resp;
}

bool AbstractMatrixTriangular::isInvertible()
{
	for (unsigned i = 0; i < this->getSize(); i++)
		if (putils::isZero((*this)(i, i)))
			return false;

	return true;
}

Vector AbstractMatrixTriangular::linearSolve(const Vector& rhs)
{
	if (rhs.getSize() != this->getSize())
		throw
			std::logic_error(messages::RHS_NOT_COMP);

	if (!this->isInvertible()) throw std::logic_error(messages::MATRIX_SINGULAR);

	return this->findSolutionByBackSubstitution(*this, rhs);
}
