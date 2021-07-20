#include "pch.h"
#include "MatrixSquare.h"


void MatrixSquare::swapRowsBellow(const unsigned int& idxPivot)
{
	unsigned int idxMax = idxPivot;
	double valMax = std::abs((*_matU)(idxPivot, idxPivot));
	for (unsigned int i = idxPivot + 1; i < _matU->getSize(); i++)
		if (std::abs((*_matU)(i, idxPivot)) > valMax) {
			valMax = std::abs((*_matU)(i, idxPivot));
			idxMax = i;
		}

	if (idxMax != idxPivot) {
		_matU->swapRows(idxMax, idxPivot);
		_matP->swapRows(idxMax, idxPivot);
		_matL->swapRowElements(idxMax, idxPivot, 0, idxPivot - 1);
		_coefSwaps *= -1.0;
	}
}

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
	_coefSwaps = 1.0;

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
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		resp += (*this)(i, i);
	return resp;
}

/*
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
*/

void MatrixSquare::decomposeToPlu()
{
	if (!_calcLu) {
		this->createLu();
		for (unsigned int idxPivot = 0; idxPivot < this->getSize() - 1; idxPivot++) {
			this->swapRowsBellow(idxPivot);
			if (!putils::areEqual((*_matU)(idxPivot, idxPivot), 0.0))
				this->nullifyElementBellow(idxPivot);
		}
	}

	_calcLu = true;
}

double MatrixSquare::determinant()
{
	this->decomposeToPlu();

	double resp{_coefSwaps};

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*_matU)(i, i);

	return resp;
}
