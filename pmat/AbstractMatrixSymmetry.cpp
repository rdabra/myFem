#include "pch.h"
#include "AbstractMatrixSymmetry.h"



void AbstractMatrixSymmetry::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	_matTri.setValue(value, rowIndex, columnIndex);
}

MatrixSquare AbstractMatrixSymmetry::toMatrixSquare() const
{
	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	}

	return resp;
}

void AbstractMatrixSymmetry::reset(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matTri.reset(size);
}

bool AbstractMatrixSymmetry::operator==(AbstractMatrixSymmetry& matrix) const
{
	return _matTri == matrix._matTri;
}


void AbstractMatrixSymmetry::plus(const AbstractMatrixSymmetry& matrix, AbstractMatrixSymmetry& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) + matrix(i, j), i, j);
}

void AbstractMatrixSymmetry::addBy(const AbstractMatrixSymmetry& matrix)
{
	_matTri.addBy(matrix._matTri);
}

double AbstractMatrixSymmetry::dotProduct(const AbstractMatrixSymmetry& matrix) const
{
	this->validateOperands(matrix);
	double resp{ 0.0 };
	for (unsigned i = 0; i < this->getSize(); i++) {
		for (unsigned j = 0; j < i; j++)
			resp += 2.0 * (*this)(i, j) * matrix(i, j);
		resp += (*this)(i, i) * matrix(i, i);
	}

	return resp;
}


void AbstractMatrixSymmetry::minus(const AbstractMatrixSymmetry& matrix, AbstractMatrixSymmetry& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) - matrix(i, j), i, j);
}

void AbstractMatrixSymmetry::subtractBy(const AbstractMatrixSymmetry& matrix)
{
	_matTri.subtractBy(matrix._matTri);
}

void AbstractMatrixSymmetry::multiplyBy(const double& scalar)
{
	_matTri.multiplyBy(scalar);
}

double AbstractMatrixSymmetry::frobeniusNorm() const
{
	return std::sqrt(this->dotProduct((*this)));
}
