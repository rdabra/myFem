#include "pch.h"
#include "MatrixSquare.h"

void MatrixSquare::fillLU()
{
	if (!_calcLU) {
		_calcLU = true;
	}
}

void MatrixSquare::createLU()
{
	if (!_createLU) {
		//		_matP = new MatrixTriangular(_rowSize, true);
		_matL = new MatrixTriangular(_rowSize, true);
		_matU = new MatrixTriangular(_rowSize, false);
		_createLU = true;
	}
}

MatrixSquare::~MatrixSquare()
{
	if (_createLU) {
		delete _matL;
		delete _matU;
		_createLU = false;
	}
}

void MatrixSquare::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	Matrix::setValue(value, rowIndex, columnIndex);
	_calcLU = false;
}

double MatrixSquare::trace() const
{
	double resp = 0.0;
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		resp += (*this)(i, i);
	return resp;
}

double MatrixSquare::determinant() const
{
	return 0.0;
}