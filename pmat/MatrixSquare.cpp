#include "pch.h"
#include "MatrixSquare.h"

void MatrixSquare::fillLU()
{
	if (!_calcLU) {
		this->createLU();

		for (unsigned int i = 1, unsigned int idxBase = 0; i < _matU->getSize(); i++, idxBase++) {
			if (!putils::areEqual((*this)(idxBase, idxBase), 0.0))
				for (unsigned int j = 0; i < _matU->getSize(); i++) {
					_matL->setValue(i, j, (*this)(i, j) / (*this)(idxBase, idxBase));
					for (unsigned int k = 0; k < _matU->getSize(); k++)
						_matU->setValue(i, k, (*_matU)(i, k) - (*_matU)(idxBase, k) * (*_matL)(i, j));
				}
			else {

			}
		}

		_calcLU = true;
	}

}


void MatrixSquare::createLU()
{
	this->destroyLU();

	_matU = new MatrixSquare(*this);
	_matP = new MatrixSquare(this->getSize());
	_matL = new MatrixSquare(this->getSize());

	for (unsigned int j = 1; j < this->getSize(); j++) {
		_matL->setValue(j, j, 1.0);
		_matP->setValue(j, j, 1.0);
	}

	_createLU = true;
}

void MatrixSquare::destroyLU()
{
	if (_createLU) {
		delete _matL;
		delete _matP;
		delete _matU;
	}
}

MatrixSquare::~MatrixSquare()
{
	this->destroyLU();
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