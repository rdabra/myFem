#include "pch.h"
#include "MatrixSquare.h"


void MatrixSquare::swapRowsBellow(const unsigned int& idxPivot)
{
	unsigned int idxMax = idxPivot;
	double valMax = std::abs((*_matsPLU.matU)(idxPivot, idxPivot));
	for (unsigned int i = idxPivot + 1; i < _matsPLU.matU->getSize(); i++)
		if (std::abs((*_matsPLU.matU)(i, idxPivot)) > valMax) {
			valMax = std::abs((*_matsPLU.matU)(i, idxPivot));
			idxMax = i;
		}

	if (idxMax != idxPivot) {
		_matsPLU.matU->swapRows(idxMax, idxPivot);
		_matsPLU.matP->swapRows(idxMax, idxPivot);
		if (idxPivot > 0)
			_matsPLU.matL->swapRowElements(idxMax, idxPivot, 0, idxPivot - 1);
		_changeSignForDet = !_changeSignForDet;
	}
}

void MatrixSquare::nullifyElementBellow(const unsigned int& idxPivot) const
{
	for (unsigned int i = idxPivot + 1; i < _matsPLU.matU->getSize(); i++) {
		_matsPLU.matL->setValue((*_matsPLU.matU)(i, idxPivot) / (*_matsPLU.matU)(idxPivot, idxPivot), i, idxPivot);
		for (unsigned int j = idxPivot; j < _matsPLU.matU->getSize(); j++)
			_matsPLU.matU->setValue((*_matsPLU.matU)(i, j) - (*_matsPLU.matU)(idxPivot, j) * (*_matsPLU.matL)(i, idxPivot), i, j);
	}
}

void MatrixSquare::createLu()
{
	this->destroyLu();

	_matsPLU.matU = new MatrixSquare(*this);
	_matsPLU.matP = new MatrixSquare(this->getSize());
	_matsPLU.matL = new MatrixSquare(this->getSize());
	_changeSignForDet = false;

	for (unsigned int j = 0; j < this->getSize(); j++) {
		_matsPLU.matL->setValue(1.0, j, j);
		_matsPLU.matP->setValue(1.0, j, j);
	}

	_createLu = true;
}

void MatrixSquare::destroyLu() const
{
	if (_createLu) {
		delete _matsPLU.matL;
		delete _matsPLU.matP;
		delete _matsPLU.matU;
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

MatrixSquare MatrixSquare::operator+(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSquare MatrixSquare::operator-(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->minus(matrix, resp);

	return resp;
}

MatrixSquare MatrixSquare::operator*(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->times(matrix, resp);

	return resp;
}

MatrixSquare MatrixSquare::operator*(const double& scalar) const
{
	MatrixSquare resp(this->getSize());
	this->times(scalar, resp);

	return resp;
}

void MatrixSquare::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	Matrix::setValue(value, rowIndex, columnIndex);
	_calcLu = false;
}

double MatrixSquare::trace() const
{
	double resp = 0.0;
	for (unsigned int i = 0; i < this->getSize(); i++)
		resp += (*this)(i, i);
	return resp;
}


const PLU& MatrixSquare::getPLU()
{
	if (!_calcLu) {
		this->createLu();
		for (unsigned int idxPivot = 0; idxPivot < _matsPLU.matU->getSize() - 1; idxPivot++) {
			this->swapRowsBellow(idxPivot);
			if (!putils::areEqual((*_matsPLU.matU)(idxPivot, idxPivot), 0.0))
				this->nullifyElementBellow(idxPivot);
		}
	}

	_calcLu = true;


	return _matsPLU;
}

double MatrixSquare::determinant()
{
	this->getPLU();

	double resp{ 1.0 };

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*_matsPLU.matU)(i, i);

	if (_changeSignForDet) resp = -resp;

	return resp;
}
