#include "pch.h"
#include "AbstractMatrixSymAntiSym.h"



void AbstractMatSymSkewSym::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	_matTri.setValue(value, rowIndex, columnIndex);
}

void AbstractMatSymSkewSym::reset(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matTri.reset(size, true);
}

bool AbstractMatSymSkewSym::operator==(AbstractMatSymSkewSym& matrix) const
{
	return _matTri == matrix._matTri;
}


void AbstractMatSymSkewSym::plus(const AbstractMatSymSkewSym& matrix, AbstractMatSymSkewSym& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) + matrix(i, j), i, j);
}

void AbstractMatSymSkewSym::addBy(const AbstractMatSymSkewSym& matrix)
{
	_matTri.addBy(matrix._matTri);
}

double AbstractMatSymSkewSym::dotProduct(const AbstractMatSymSkewSym& matrix) const
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


void AbstractMatSymSkewSym::minus(const AbstractMatSymSkewSym& matrix, AbstractMatSymSkewSym& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) - matrix(i, j), i, j);
}

void AbstractMatSymSkewSym::subtractBy(const AbstractMatSymSkewSym& matrix)
{
	_matTri.subtractBy(matrix._matTri);
}

void AbstractMatSymSkewSym::multiplyBy(const double& scalar)
{
	_matTri.multiplyBy(scalar);
}

double AbstractMatSymSkewSym::frobeniusNorm() const
{
	return std::sqrt(this->dotProduct((*this)));
}
