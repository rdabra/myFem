#include "pch.h"
#include "MatrixSquare.h"

void MatrixSquare::nullifyElementBellow(const unsigned int& idxPivot) const
{
	for (unsigned int i = idxPivot + 1; i < _matU->getSize(); i++) {
		_matL->setValue((*_matU)(i, idxPivot) / (*_matU)(idxPivot, idxPivot), i, idxPivot);
		for (unsigned int j = idxPivot; j < _matU->getSize(); j++)
			_matU->setValue((*_matU)(i, j) - (*_matU)(idxPivot, j) * (*_matL)(i, idxPivot), i, j);
	}
}

void MatrixSquare::createLu()
{
	this->destroyLu();

	_matU = new MatrixSquare(*this);
	_matP = new MatrixSquare(this->getSize());
	_matL = new MatrixSquare(this->getSize());

	for (unsigned int j = 0; j < this->getSize(); j++) {
		_matL->setValue(1.0, j, j);
		_matP->setValue(1.0, j, j);
	}

	_createLu = true;
}

void MatrixSquare::destroyLu() const
{
	if (_createLu) {
		delete _matL;
		delete _matP;
		delete _matU;
	}
}


MatrixSquare::~MatrixSquare()
{
	this->destroyLu();
}

MatrixSquare& MatrixSquare::operator=(const MatrixSquare& matrix)
{
	if (!(this == &matrix)) Matrix::operator=(matrix);
	return (*this);
}

MatrixSquare& MatrixSquare::operator=(MatrixSquare&& matrix) noexcept
{
	Matrix::operator=(std::move(matrix));
	return (*this);
}

void MatrixSquare::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	Matrix::setValue(value, rowIndex, columnIndex);
	_calcLu = false;
}

double MatrixSquare::trace() const
{
	double resp = 0.0;
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		resp += (*this)(i, i);
	return resp;
}

void MatrixSquare::decomposeToPlu()
{
	if (!_calcLu) {
		this->createLu();
		_numExchangesP = 0;
		unsigned int idxPivot{0};
		while (idxPivot < _matU->getSize() - 1) {
			if (!putils::areEqual((*_matU)(idxPivot, idxPivot), 0.0)) {
				this->nullifyElementBellow(idxPivot);
				idxPivot++;
			}
			else {
				unsigned int i = idxPivot + 1;
				bool swap{false};
				while (!swap && i < _matU->getSize()) {
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

	_calcLu = true;
}

double MatrixSquare::determinant() 
{
	this->decomposeToPlu();

	double resp{pow(-1.0, _numExchangesP)};

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*_matU)(i, i);

	return resp;
}
