#include "pch.h"
#include "MatrixSquare.h"


void MatrixSquare::swapRowsBellow(MatrixSquare& matU, const unsigned int& idxPivot)
{
	unsigned int idxMax = idxPivot;
	double valMax = std::abs(matU(idxPivot, idxPivot));
	for (unsigned int i = idxPivot + 1; i < matU.getSize(); i++)
		if (std::abs(matU(i, idxPivot)) > valMax) {
			valMax = std::abs(matU(i, idxPivot));
			idxMax = i;
		}

	if (idxMax != idxPivot) {
		matU.swapRows(idxMax, idxPivot);
		_matsPLU.matP->swapRows(idxMax, idxPivot);
		if (idxPivot > 0)
			_matsPLU.matL->swapRowElements(idxMax, idxPivot, 0, idxPivot - 1);
		_changeSignForDet = !_changeSignForDet;
	}
}

void MatrixSquare::nullifyElementBellow(MatrixSquare& matU, const unsigned int& idxPivot) const
{
	for (unsigned int i = idxPivot + 1; i < matU.getSize(); i++) {
		_matsPLU.matL->setValue(matU(i, idxPivot) / matU(idxPivot, idxPivot), i, idxPivot);
		for (unsigned int j = idxPivot; j < matU.getSize(); j++)
			matU.setValue(
				matU(i, j) - matU(idxPivot, j) * (*_matsPLU.matL)(i, idxPivot), i, j);
	}
}


void MatrixSquare::createLu()
{
	this->destroyLu();

	_matsPLU.matP = new MatrixSquare(this->getSize());
	_matsPLU.matU = new MatrixTriangular(this->getSize(), false);
	_matsPLU.matL = new MatrixTriangular(this->getSize(), true);
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


void MatrixSquare::decomposePlu()
{
	if (!_calcLu) {
		this->createLu();
		MatrixSquare matU(*this);
		for (unsigned int idxPivot = 0; idxPivot < matU.getSize() - 1; idxPivot++) {
			this->swapRowsBellow(matU, idxPivot);
			if (!putils::areEqual(matU(idxPivot, idxPivot), 0.0))
				this->nullifyElementBellow(matU, idxPivot);
		}
		_matsPLU.matU = new MatrixTriangular(matU.extractUpperPart());
	}

	_calcLu = true;
}

void MatrixSquare::findInverseTriangular(MatrixSquare* matrix, bool lower, MatrixSquare* resp) const
{
	std::vector<unsigned> ids(matrix->getSize());

	if (lower)
		for (unsigned int k = 0; k < matrix->getSize(); k++) ids[k] = k;
	else
		for (unsigned int k = matrix->getSize(); k != 0; k--) ids[k - 1] = k - 1;

	for (unsigned int idxPivot = 0; idxPivot < matrix->getSize(); idxPivot++) {
		resp->setValue(1.0 / (*matrix)(ids[idxPivot], ids[idxPivot]), ids[idxPivot], ids[idxPivot]);
		for (unsigned int i = idxPivot + 1; i < matrix->getSize(); i++) {
			double num{ 0.0 };
			for (unsigned int j = idxPivot; j < i; j++)
				num -= (*matrix)(ids[i], ids[j]) * (*resp)(ids[j], ids[idxPivot]);
			resp->setValue(num / (*matrix)(ids[i], ids[i]), ids[i], ids[idxPivot]);
		}
	}
}

const PLU& MatrixSquare::getPLU()
{
	this->decomposePlu();


	return _matsPLU;
}

bool MatrixSquare::isInvertible()
{
	return !putils::areEqual(this->determinant(), 0.0);
}

MatrixTriangular MatrixSquare::extractLowerPart() const
{
	MatrixTriangular resp(this->getSize(), true);
	for (unsigned int i = 0; i < this->getSize(); ++i)
		for (unsigned int j = 0; j <= i; ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

MatrixTriangular MatrixSquare::extractUpperPart() const
{
	MatrixTriangular resp(this->getSize(), false);
	for (unsigned int i = 0; i < this->getSize(); ++i)
		for (unsigned int j = i; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

double MatrixSquare::determinant()
{
	this->decomposePlu();

	double resp{ 1.0 };

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*_matsPLU.matU)(i, i);

	if (_changeSignForDet) resp = -resp;

	return resp;
}
