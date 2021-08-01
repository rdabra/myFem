#include "pch.h"
#include "MatrixTriangular.h"


MatrixTriangular::MatrixTriangular(const unsigned& size, bool isLower)
{
	_rowSize = size;
	_columnSize = size;
	_isLower = isLower;
	_matrix.resize(this->MatrixTriangular::getVectorSize());
}

MatrixTriangular::MatrixTriangular(const MatrixTriangular& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_isLower = matrix.isLower();
	_matrix.resize(matrix.getVectorSize());

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->MatrixTriangular::setValue(matrix(i, j), i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				this->MatrixTriangular::setValue(matrix(i, j), i, j);
}

MatrixTriangular::MatrixTriangular(MatrixTriangular&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_isLower = matrix.isLower();
	_matrix = std::move(matrix._matrix);
	matrix.~MatrixTriangular();
}

void MatrixTriangular::resize(const unsigned& size, bool isLower)
{
	_matrix.clear();
	_rowSize = size;
	_columnSize = size;
	_isLower = isLower;
	_matrix.resize(this->getVectorSize());
}

void MatrixTriangular::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	validateIndex(rowIndex, columnIndex);
	if ((_isLower && columnIndex > rowIndex) || (!_isLower && columnIndex < rowIndex))
		throw std::out_of_range(messages::INDEX_OUT);

	_matrix[this->getVectorIndex(rowIndex, columnIndex)] = value;
}

const double& MatrixTriangular::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	validateIndex(rowIndex, columnIndex);

	const bool isZero = (_isLower && columnIndex > rowIndex) || ((!_isLower) && columnIndex < rowIndex);

	return isZero ? putils::ZERO : _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

bool MatrixTriangular::operator==(MatrixTriangular& matrix) const
{
	if (this->isLower() != matrix.isLower() || this->getSize() != matrix.getSize()) return false;

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++) {
				if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;
			}
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;

	return true;
}


MatrixTriangular& MatrixTriangular::operator=(const MatrixTriangular& matrix)
{
	if (!(this == &matrix)) {
		_matrix.clear();
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_isLower = matrix.isLower();
		_matrix.resize(matrix.getVectorSize());
		if (this->isLower())
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					this->setValue(matrix(i, j), i, j);
		else
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = i; j < this->getSize(); j++)
					this->setValue(matrix(i, j), i, j);
	}

	return (*this);
}

MatrixTriangular& MatrixTriangular::operator=(MatrixTriangular&& matrix) noexcept
{
	_matrix.clear();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_isLower = matrix.isLower();
	_matrix = std::move(matrix._matrix);

	matrix.~MatrixTriangular();

	return (*this);
}

MatrixSquare MatrixTriangular::asMatrixSquare() const
{
	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	}

	return resp;	
}

double MatrixTriangular::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				resp += (*this)(i, j) * matrix(i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				resp += (*this)(i, j) * matrix(i, j);

	return resp;
}

void MatrixTriangular::plus(const MatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (_isLower == matrix.isLower()) {
		if (this->isLower())
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					resp.setValue((*this)(i, j) + matrix(i, j), i, j);
		else
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = i; j < this->getSize(); j++)
					resp.setValue((*this)(i, j) + matrix(i, j), i, j);
	}
	else {
		if (this->isLower())
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) + matrix(i, i), i, i);
					else {
						resp.setValue((*this)(i, j), i, j);
						resp.setValue(matrix(j, i), j, i);
					}
		else
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) + matrix(i, i), i, i);
					else {
						resp.setValue((*this)(j, i), j, i);
						resp.setValue(matrix(i, j), i, j);
					}
	}
}

void MatrixTriangular::addBy(const MatrixTriangular& matrix)
{
	this->validateOperands(matrix);

	if (_isLower != matrix.isLower())
		throw std::logic_error(messages::NONCOMPT_ARG);

	if (this->isLower())
		for (unsigned i = 0; i < this->getRowSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->setValue((*this)(i, j) + matrix(i, j), i, j);
	else
		for (unsigned i = 0; i < this->getRowSize(); i++)
			for (unsigned j = i; j < this->getColumnSize(); j++)
				this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

void MatrixTriangular::minus(const MatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (_isLower == matrix.isLower()) {
		if (this->isLower())
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					resp.setValue((*this)(i, j) - matrix(i, j), i, j);
		else
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = i; j < this->getSize(); j++)
					resp.setValue((*this)(i, j) - matrix(i, j), i, j);
	}
	else {
		if (this->isLower())
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) - matrix(i, i), i, i);
					else {
						resp.setValue((*this)(i, j), i, j);
						resp.setValue(-matrix(j, i), j, i);
					}
		else
			for (unsigned i = 0; i < this->getSize(); i++)
				for (unsigned j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) - matrix(i, i), i, i);
					else {
						resp.setValue((*this)(j, i), j, i);
						resp.setValue(-matrix(i, j), i, j);
					}
	}
}

MatrixSquare MatrixTriangular::operator+(const MatrixTriangular& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSquare MatrixTriangular::operator-(const MatrixTriangular& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->minus(matrix, resp);

	return resp;
}

void MatrixTriangular::subtractBy(const MatrixTriangular& matrix)
{
	if (_isLower != matrix.isLower())
		throw std::logic_error(messages::NONCOMPT_ARG);

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->setValue((*this)(i, j) - matrix(i, j), i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void MatrixTriangular::times(const MatrixSquare& matrix, MatrixSquare& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	if (this->isLower()) {
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j < this->getSize(); j++) {
				double aux = 0.0;
				for (unsigned k = 0; k <= i; k++)
					aux += (*this)(i, k) * matrix(k, j);
				resp.setValue(aux, i, j);
			}
	}
	else {
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j < this->getSize(); j++) {
				double aux = 0.0;
				for (unsigned k = i; k < this->getSize(); k++)
					aux += (*this)(i, k) * matrix(k, j);
				resp.setValue(aux, i, j);
			}
	}
}

void MatrixTriangular::times(const Vector& vector, Vector& resp) const
{
	this->validateVectorMult(vector);
	this->validateVectorRespMult(resp);

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++) {
			double aux = 0.0;
			for (unsigned k = 0; k <= i; k++)
				aux += (*this)(i, k) * vector(k);
			resp.setValue(aux, i);
		}
	else
		for (unsigned i = 0; i < this->getSize(); i++) {
			double aux = 0.0;
			for (unsigned k = i; k < this->getSize(); k++)
				aux += (*this)(i, k) * vector(k);
			resp.setValue(aux, i);
		}
}

void MatrixTriangular::times(const double& scalar, MatrixTriangular& resp) const
{
	if (_isLower != resp.isLower())
		throw std::logic_error(messages::NONCOMPT_ARG);

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				resp.setValue((*this)(i, j) * scalar, i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				resp.setValue((*this)(i, j) * scalar, i, j);
}

MatrixSquare MatrixTriangular::operator*(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->times(matrix, resp);

	return resp;
}

MatrixTriangular MatrixTriangular::operator*(const double& scalar) const
{
	MatrixTriangular resp(this->getSize(), this->isLower());
	this->times(scalar, resp);

	return resp;
}

Vector MatrixTriangular::operator*(const Vector& vector) const
{
	Vector resp(this->getSize());
	this->times(vector, resp);

	return resp;
}

void MatrixTriangular::multiplyBy(const double& scalar)
{
	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->setValue((*this)(i, j) * scalar, i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				this->setValue((*this)(i, j) * scalar, i, j);
}

double MatrixTriangular::frobeniusNorm() const
{
	return sqrt(this->dotProduct((*this)));
}

void MatrixTriangular::transpose()
{
	Matrix::transpose();
	_isLower = !_isLower;
}

MatrixSquare MatrixTriangular::getSwappedByRows(const unsigned& rowIndexA, const unsigned& rowIndexB) const
{
	this->validateIndex(rowIndexA, 0);
	this->validateIndex(rowIndexB, 0);

	MatrixSquare resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i) {
		unsigned k = i;
		if (i == rowIndexA) k = rowIndexB;
		else if (i == rowIndexB) k = rowIndexA;
		for (unsigned j = 0; j < this->getSize(); ++j)
			resp.setValue((*this)(k, j), i, j);
	}

	return resp;
}

void MatrixTriangular::swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB,
                                       const unsigned& startColumn, const unsigned& endColumn)
{
	if ((startColumn > endColumn) || (_isLower && (endColumn > rowIndexA || endColumn > rowIndexB)) ||
		((!_isLower) && (startColumn < rowIndexA || startColumn < rowIndexB)))
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::swapRowElements(rowIndexA, rowIndexB, startColumn, endColumn);
}

MatrixSquare MatrixTriangular::getSwappedByColumns(const unsigned& columnIndexA, const unsigned& columnIndexB) const
{
	this->validateIndex(0, columnIndexA);
	this->validateIndex(0, columnIndexB);

	MatrixSquare resp(this->getSize());
	for (unsigned j = 0; j < this->getSize(); ++j) {
		unsigned k = j;
		if (j == columnIndexA) k = columnIndexB;
		else if (j == columnIndexB) k = columnIndexA;
		for (unsigned i = 0; i < this->getSize(); ++i)
			resp.setValue((*this)(i, k), i, j);
	}

	return resp;
}

void MatrixTriangular::swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                          const unsigned& startRow, const unsigned& endRow)
{
	if ((startRow > endRow) || (_isLower && (columnIndexA > startRow || columnIndexB > startRow)) ||
		((!_isLower) && (endRow > columnIndexA || endRow > columnIndexB)))
		throw std::out_of_range(messages::INDEX_OUT);

	Matrix::swapColumnElements(columnIndexA, columnIndexB, startRow, endRow);
}

void MatrixTriangular::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	if (this->isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->setValue(dist(rng), i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i + 1; j < this->getSize(); j++)
				this->setValue(dist(rng), i, j);
}

double MatrixTriangular::determinant()
{
	double resp = 1.0;

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*this)(i, i);

	return resp;
}
