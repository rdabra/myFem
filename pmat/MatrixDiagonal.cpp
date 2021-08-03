#include "pch.h"
#include "MatrixDiagonal.h"
#include "MatrixSymmetric.h" // In order to define the class completely
#include "MatrixAntiSymmetric.h" // In order to define the class completely


void MatrixDiagonal::decomposeToPlu()
{
	if (!_calcLu) {
		this->createLu();
		for (unsigned i = 0; i < this->getSize(); i++)
			_matsPLU.matU->setValue((*this)(i, i), i, i);

		_calcLu = true;
	}
}

void MatrixDiagonal::decomposeToStrictLu()
{
	if (!this->isInvertible()) throw std::out_of_range(messages::MATRIX_NOT_LU);
	this->decomposeToPlu();
}

void MatrixDiagonal::decomposeToSas()
{
	if (!_calcSas) {
		this->createSas();
		for (unsigned i = 0; i < this->getSize(); ++i) {
			_matsSAS.matS->setValue(.5000000000 * (*this)(i, i), i, i);
			_matsSAS.matAS->setValue((*_matsSAS.matS)(i,i), i, i);
		}
		_calcSas = true;
	}
}

MatrixDiagonal::MatrixDiagonal(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matrix.resize(this->MatrixDiagonal::getVectorSize());
}

MatrixDiagonal::MatrixDiagonal(const MatrixDiagonal& matrix)
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_matrix.resize(this->MatrixDiagonal::getVectorSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		this->MatrixDiagonal::setValue(matrix(i, i), i, i);
}

void MatrixDiagonal::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	validateIndex(rowIndex, columnIndex);

	if (columnIndex != rowIndex) throw std::out_of_range(messages::INDEX_OUT);

	_matrix[this->getVectorIndex(rowIndex, rowIndex)] = value;
}

double MatrixDiagonal::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	validateIndex(rowIndex, columnIndex);

	return rowIndex != columnIndex ? putils::ZERO : _matrix[this->getVectorIndex(rowIndex, rowIndex)];
}

MatrixDiagonal& MatrixDiagonal::operator=(const MatrixDiagonal& matrix)
{
	_matrix.clear();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix.resize(_rowSize);
	for (unsigned i = 0; i < _rowSize; i++)
		_matrix[i] = matrix._matrix[i];

	return (*this);
}

MatrixDiagonal& MatrixDiagonal::operator=(MatrixDiagonal&& matrix) noexcept
{
	_matrix.clear();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix = std::move(matrix._matrix);

	matrix.~MatrixDiagonal();

	return (*this);
}

bool MatrixDiagonal::operator==(MatrixDiagonal& matrix) const
{
	for (unsigned i = 0; i < this->getRowSize(); i++)
		if (!putils::areEqual((*this)(i, i), matrix(i, i))) return false;
	return true;
}

MatrixSquare MatrixDiagonal::asMatrixSquare() const
{
	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	}

	return resp;
}

MatrixDiagonal MatrixDiagonal::operator+(const MatrixDiagonal& matrix) const
{
	MatrixDiagonal resp(matrix.getSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixDiagonal MatrixDiagonal::operator-(const MatrixDiagonal& matrix) const
{
	MatrixDiagonal resp(matrix.getSize());
	this->minus(matrix, resp);

	return resp;
}

double MatrixDiagonal::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp += (*this)(i, i) * matrix(i, i);

	return resp;
}

void MatrixDiagonal::plus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp.setValue((*this)(i, i) + matrix(i, i), i, i);
}

void MatrixDiagonal::addBy(const MatrixDiagonal& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, i) + matrix(i, i), i, i);
}

void MatrixDiagonal::minus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp.setValue((*this)(i, i) - matrix(i, i), i, i);
}

void MatrixDiagonal::subtractBy(const MatrixDiagonal& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, i) - matrix(i, i), i, i);
}


void MatrixDiagonal::times(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp.setValue((*this)(i, i) * matrix(i, i), i, i);
}

void MatrixDiagonal::times(const Vector& vector, Vector& resp) const
{
	this->validateVectorMult(vector);
	this->validateVectorRespMult(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp.setValue((*this)(i, i) * vector(i), i);
}

void MatrixDiagonal::times(const double& scalar, MatrixDiagonal& resp) const
{
	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp.setValue((*this)(i, i) * scalar, i, i);
}

void MatrixDiagonal::multiplyBy(const double& scalar)
{
	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, i) * scalar, i, i);
}

double MatrixDiagonal::frobeniusNorm() const
{
	double resp = 0.0;

	for (unsigned i = 0; i < this->getRowSize(); i++)
		resp += (*this)(i, i) * (*this)(i, i);

	return sqrt(resp);
}


void MatrixDiagonal::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator
	std::mt19937 rng;

	//Initialize with non-deterministic seeds
	rng.seed(std::random_device{}());

	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue(dist(rng), i, i);
}

double MatrixDiagonal::determinant()
{
	double resp = 1.0000000000;

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*this)(i, i);

	return resp;
}

bool MatrixDiagonal::isStrictLUDecomposable()
{
	for (unsigned i = 0; i < this->getSize(); i++)
		if (putils::areEqual((*this)(i, i), putils::ZERO)) return false;

	return true;
}

bool MatrixDiagonal::isInvertible()
{
	return this->isStrictLUDecomposable();
}

MatrixTriangular MatrixDiagonal::extractLowerPart() const
{
	MatrixTriangular resp(this->getSize(), true);
	for (unsigned i = 0; i < this->getSize(); i++)
		resp.setValue((*this)(i, i), i, i);

	return resp;
}

MatrixTriangular MatrixDiagonal::extractUpperPart() const
{
	MatrixTriangular resp(this->getSize(), false);
	for (unsigned i = 0; i < this->getSize(); i++)
		resp.setValue((*this)(i, i), i, i);

	return resp;
}

MatrixSquare MatrixDiagonal::getInverse()
{
	if (!this->isInvertible()) throw std::out_of_range(messages::MATRIX_SINGULAR);

	MatrixSquare resp(this->getSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		resp.setValue(1.0000000000 / (*this)(i, i), i, i);

	return resp;
}

bool MatrixDiagonal::isPositiveDefinite()
{
	for (unsigned i = 0; i < this->getSize(); i++)
		if ((*this)(i, i) < putils::ZERO) return false;

	return true;
}
