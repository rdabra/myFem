#include "pch.h"
#include "MatrixSquare.h"


void MatrixSquare::swapRowsBellow(MatrixSquare& matU, const unsigned& idxPivot)
{
	unsigned idxMax = idxPivot;
	double valMax = std::abs(matU(idxPivot, idxPivot));
	for (unsigned i = idxPivot + 1; i < matU.getSize(); i++)
		if (std::abs(matU(i, idxPivot)) > valMax) {
			valMax = std::abs(matU(i, idxPivot));
			idxMax = i;
		}

	if (idxMax != idxPivot) {
		matU.swapRows(idxMax, idxPivot);
		_matsPLU.matP->swapRows(idxMax, idxPivot);
		if (idxPivot > 0)
			_matsPLU.matL->swapRowElements(idxMax, idxPivot, 0, idxPivot - 1);
		_matsPLU.swappedRows.emplace_back(idxMax, idxPivot);
		_changeSignForDet = !_changeSignForDet;
	}
}

void MatrixSquare::nullifyElementBellow(MatrixSquare& matU, const unsigned& idxPivot) const
{
	for (unsigned i = idxPivot + 1; i < matU.getSize(); i++) {
		_matsPLU.matL->setValue(matU(i, idxPivot) / matU(idxPivot, idxPivot), i, idxPivot);
		for (unsigned j = idxPivot; j < matU.getSize(); j++)
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

	for (unsigned j = 0; j < this->getSize(); j++) {
		_matsPLU.matL->setValue(1.0, j, j);
		_matsPLU.matP->setValue(1.0, j, j);
	}

	_createLu = true;
}

void MatrixSquare::destroyLu() 
{
	if (_createLu) {
		delete _matsPLU.matL;
		delete _matsPLU.matP;
		delete _matsPLU.matU;
		_createLu = false;
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

void MatrixSquare::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	Matrix::setValue(value, rowIndex, columnIndex);
	_calcLu = false;
}

double MatrixSquare::trace() const
{
	double resp = 0.0;
	for (unsigned i = 0; i < this->getSize(); i++)
		resp += (*this)(i, i);
	return resp;
}


void MatrixSquare::decomposeToPlu(bool strictLU)
{
	if (!_calcLu) {
		this->createLu();
		MatrixSquare matU(*this);
		if (strictLU) {
			for (unsigned idxPivot = 0; idxPivot < matU.getSize() - 1; idxPivot++) {
				if (putils::areEqual(matU(idxPivot, idxPivot), 0.0)) {
					this->destroyLu();
					throw std::logic_error(messages::MATRIX_NOT_LU);
				}
				this->nullifyElementBellow(matU, idxPivot);
			}
		}
		else {
			for (unsigned idxPivot = 0; idxPivot < matU.getSize() - 1; idxPivot++) {
				this->swapRowsBellow(matU, idxPivot);
				if (!putils::areEqual(matU(idxPivot, idxPivot), 0.0)) 
					this->nullifyElementBellow(matU, idxPivot);
			}
		}

		for (unsigned i = 0; i < matU.getSize(); ++i)
			for (unsigned j = i; j < matU.getSize(); ++j)
				_matsPLU.matU->setValue(matU(i, j), i, j);
		_calcLu = true;
	}
}

void MatrixSquare::findInverseByBackSubstitution(MatrixTriangular* matrix, MatrixTriangular* resp) const
{
	std::vector<unsigned> ids(matrix->getSize());

	if (matrix->isLower())
		for (unsigned k = 0; k < matrix->getSize(); k++) ids[k] = k;
	else
		for (unsigned k = 0; k < matrix->getSize(); k++) ids[k] = matrix->getSize() - k - 1;

	for (unsigned idxPivot = 0; idxPivot < matrix->getSize(); idxPivot++) {
		resp->setValue(1.0 / (*matrix)(ids[idxPivot], ids[idxPivot]), ids[idxPivot], ids[idxPivot]);
		for (unsigned i = idxPivot + 1; i < matrix->getSize(); i++) {
			double num{0.0};
			for (unsigned j = idxPivot; j < i; j++)
				num -= (*matrix)(ids[i], ids[j]) * (*resp)(ids[j], ids[idxPivot]);
			resp->setValue(num / (*matrix)(ids[i], ids[i]), ids[i], ids[idxPivot]);
		}
	}
}

const PLU& MatrixSquare::getPLU()
{
	this->decomposeToPlu(false);


	return _matsPLU;
}

const PLU& MatrixSquare::getLU()
{
	this->decomposeToPlu(true);

	
	return _matsPLU;
}

bool MatrixSquare::isLUDecomposable()
{
	try {
		this->decomposeToPlu(true);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool MatrixSquare::isInvertible()
{
	return !putils::areEqual(this->determinant(), 0.0);
}

MatrixTriangular MatrixSquare::extractLowerPart() const
{
	MatrixTriangular resp(this->getSize(), true);
	for (unsigned i = 0; i < this->getSize(); ++i)
		for (unsigned j = 0; j <= i; ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

MatrixTriangular MatrixSquare::extractUpperPart() const
{
	MatrixTriangular resp(this->getSize(), false);
	for (unsigned i = 0; i < this->getSize(); ++i)
		for (unsigned j = i; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

MatrixSquare MatrixSquare::getInverse()
{
	this->decomposeToPlu(false);
	if (!this->isInvertible()) throw std::out_of_range(messages::MATRIX_SINGULAR);

	MatrixTriangular invU(this->getSize(), false);
	this->findInverseByBackSubstitution(_matsPLU.matU, &invU);

	MatrixTriangular invL(this->getSize(), true);
	this->findInverseByBackSubstitution(_matsPLU.matL, &invL);

	MatrixSquare resp(invU * invL);

	for (auto& swappedRow : _matsPLU.swappedRows)
		resp.swapColumns(swappedRow.first, swappedRow.second);

	return resp;
}

// According to Golub & Van Loan, "Matrix Computations", ISBN  9789380250755, p. 161.
bool MatrixSquare::isPositiveDefinite()
{
	if (this->isLUDecomposable()) {
		for (unsigned i = 0; i < this->getSize(); i++)
			if ((*_matsPLU.matU)(i, i) < 0) return false;
		return true;
	}

	return false;
}

double MatrixSquare::determinant()
{
	this->decomposeToPlu(false);

	double resp{1.0};

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*_matsPLU.matU)(i, i);

	if (_changeSignForDet) resp = -resp;

	return resp;
}
