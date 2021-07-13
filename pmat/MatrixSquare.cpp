#include "pch.h"
#include "MatrixSquare.h"

void MatrixSquare::nullifyElementBellow(const unsigned int& idxPivot)
{
	for (unsigned int i = idxPivot + 1; i < _matU->getSize(); i++) {
		_matL->setValue((*_matU)(i, idxPivot) / (*_matU)(idxPivot, idxPivot), i, idxPivot);
		for (unsigned int j = idxPivot; j < _matU->getSize(); j++)
			_matU->setValue((*_matU)(i, j) - (*_matU)(idxPivot, j) * (*_matL)(i, idxPivot), i, j);
	}
}

void MatrixSquare::createLU()
{
	this->destroyLU();

	_matU = new MatrixSquare(*this);
	_matP = new MatrixSquare(this->getSize());
	_matL = new MatrixSquare(this->getSize());

	for (unsigned int j = 0; j < this->getSize(); j++) {
		_matL->setValue(1.0, j, j);
		_matP->setValue(1.0, j, j);
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

void MatrixSquare::decomposeToPLU()
{
	if (!_calcLU) {
		this->createLU();
		_numExchangesP = 0;
		unsigned int idxPivot{ 0 };
		while (idxPivot < _matU->getSize() - 1) {
			if (!putils::areEqual((*_matU)(idxPivot, idxPivot), 0.0)) {
				this->nullifyElementBellow(idxPivot);
				idxPivot++;
			}
			else {
				unsigned int i = idxPivot + 1;
				bool swap{ false };
				while (!swap && i < _matU->getSize())
				{
					if (!putils::areEqual((*_matU)(i, idxPivot), 0.0)) {
						_matU->swapRows(i, idxPivot);
						_matP->swapRows(i, idxPivot);
						_matL->swapRowElements(i, idxPivot, 0, idxPivot - 1);
						_numExchangesP++;
						swap = true;
					}
					i++;
				}
				if (!swap) idxPivot++;
			}
		}
	}

	_calcLU = true;
}

double MatrixSquare::determinant()
{
	this->decomposeToPLU();

	double resp{ pow(-1.0, _numExchangesP) };

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*_matU)(i, i);

	return resp;
}