#include "pch.h"

#include "Matrix.h"

Matrix::Matrix(const unsigned int& rowSize, const unsigned int& columnSize)
{
	_rowSize = rowSize;
	_columnSize = columnSize;
	_matrix.resize(this->Matrix::getVectorSize());
}

Matrix::Matrix(const Matrix& matrix)
{
	_rowSize = matrix.getRowSize();
	_columnSize = matrix.getColumnSize();
	_matrix.resize(this->Matrix::getVectorSize());

	for (unsigned int i = 0; i < this->Matrix::getRowSize(); i++)
		for (unsigned int j = 0; j < this->Matrix::getColumnSize(); j++)
			this->Matrix::setValue(matrix(i, j), i, j);
}

Matrix::Matrix(Matrix&& matrix) noexcept
{
	_rowSize = matrix.getRowSize();
	_columnSize = matrix.getColumnSize();
	_matrix.resize(this->Matrix::getVectorSize());

	for (unsigned int i = 0; i < this->Matrix::getRowSize(); i++)
		for (unsigned int j = 0; j < this->Matrix::getColumnSize(); j++)
			this->Matrix::setValue(matrix(i, j), i, j);

	matrix.~Matrix();
}

const double& Matrix::operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const
{
	this->validateIndex(rowIndex, columnIndex);
	return _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

void Matrix::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	this->validateIndex(rowIndex, columnIndex);
	_matrix[this->getVectorIndex(rowIndex, columnIndex)] = value;
}

Matrix& Matrix::operator=(const Matrix& matrix)
{
	if (!(this == &matrix)) {
		_matrix.clear();

		_rowSize = matrix.getRowSize();
		_columnSize = matrix.getColumnSize();
		_matrix.resize(this->getVectorSize());

		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = 0; j < this->getColumnSize(); j++)
				this->setValue(matrix(i, j), i, j);
	}

	return (*this);
}

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
	_matrix.clear();

	_rowSize = matrix.getRowSize();
	_columnSize = matrix.getColumnSize();
	_matrix = std::move(matrix._matrix);

	return (*this);
}

bool Matrix::operator==(const Matrix& matrix) const
{
	bool test{ this->getRowSize() == matrix.getRowSize() && this->getColumnSize() == matrix.getColumnSize() };

	if (test) {
		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = 0; j < this->getColumnSize(); j++)
				if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;

	}
	else return false;

	return true;
}

double Matrix::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			resp += (*this)(i, j) * matrix(i, j);

	return resp;
}

void Matrix::plus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) + matrix(i, j), i, j);
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());
	this->plus(matrix, resp);

	return resp;
}

void Matrix::addBy(const Matrix& matrix)
{
	this->validateOperands(matrix);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

void Matrix::minus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) - matrix(i, j), i, j);
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());

	this->minus(matrix, resp);

	return resp;
}

void Matrix::subtractBy(const Matrix& matrix)
{
	this->validateOperands(matrix);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void Matrix::times(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < matrix.getColumnSize(); j++) {
			double aux = 0.0;
			for (unsigned int k = 0; k < this->getColumnSize(); k++)
				aux += (*this)(i, k) * matrix(k, j);
			resp.setValue(aux, i, j);
		}
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), matrix.getColumnSize());
	this->times(matrix, resp);

	return resp;
}

void Matrix::times(const Vector& vector, Vector& resp) const
{
	this->validateVectorMult(vector);
	this->validateVectorRespMult(resp);

	for (unsigned int i = 0; i < this->getRowSize(); i++) {
		double aux = 0.0;
		for (unsigned int k = 0; k < this->getColumnSize(); k++)
			aux += (*this)(i, k) * vector(k);
		resp.setValue(aux, i);
	}
}

Vector Matrix::operator*(const Vector& vector) const
{
	Vector resp(this->getRowSize());
	this->times(vector, resp);

	return resp;
}

void Matrix::times(const double& scalar, Matrix& resp) const
{
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) * scalar, i, j);
}

Matrix Matrix::operator*(const double& scalar) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());
	this->times(scalar, resp);

	return resp;
}

void Matrix::multiplyBy(const double& scalar)
{
	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) * scalar, i, j);
}

void Matrix::multiplyRowBy(const unsigned int& rowIndex, const double& scalar)
{
	this->validateIndex(rowIndex, 0);

	for (unsigned int j = 0; j < this->getColumnSize(); j++)
		this->setValue((*this)(rowIndex, j) * scalar, rowIndex, j);
}

void Matrix::multiplyColumnBy(const unsigned int& columnIndex, const double& scalar)
{
	this->validateIndex(0, columnIndex);

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, columnIndex) * scalar, i, columnIndex);
}

void Matrix::swapRowElements(const unsigned int& rowIndexA, const unsigned int& rowIndexB,
	const unsigned int& startColumn, const unsigned int& endColumn)
{
	this->validateIndex(rowIndexA, 0);
	this->validateIndex(rowIndexB, 0);
	if (startColumn >= this->getColumnSize() || endColumn >= this->getColumnSize())
		throw std::logic_error(
			messages::INDEX_OUT);

	for (unsigned int j = startColumn; j <= endColumn; j++) {
		double tmp{ (*this)(rowIndexB, j) };
		this->setValue((*this)(rowIndexA, j), rowIndexB, j);
		this->setValue(tmp, rowIndexA, j);
	}
}

inline void Matrix::swapRows(const unsigned int& rowIndexA, const unsigned int& rowIndexB)
{
	this->swapRowElements(rowIndexA, rowIndexB, 0, this->getColumnSize() - 1);
}

void Matrix::swapColumnElements(const unsigned int& columnIndexA, const unsigned int& columnIndexB,
	const unsigned int& startRow, const unsigned int& endRow)
{
	this->validateIndex(0, columnIndexA);
	this->validateIndex(0, columnIndexA);
	if (startRow >= this->getRowSize() || endRow >= this->getRowSize()) throw std::logic_error(messages::INDEX_OUT);

	for (unsigned int i = startRow; i <= endRow; i++) {
		double tmp{ (*this)(i, columnIndexB) };
		this->setValue((*this)(i, columnIndexA), i, columnIndexB);
		this->setValue(tmp, i, columnIndexA);
	}
}


void Matrix::swapColumns(const unsigned int& columnIndexA, const unsigned int& columnIndexB)
{
	this->swapColumnElements(columnIndexA, columnIndexB, 0, this->getRowSize() - 1);
}


void Matrix::transpose()
{
	_isTransposed = !_isTransposed;
	std::swap(_rowSize, _columnSize);
}


double Matrix::frobeniusNorm() const
{
	double resp = 0.0;

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			resp += (*this)(i, j) * (*this)(i, j);

	return sqrt(resp);
}

void Matrix::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	for (unsigned int i = 0; i < this->getRowSize(); i++)
		for (unsigned int j = 0; j < this->getColumnSize(); j++)
			this->setValue(dist(rng), i, j);
}


void Matrix::validateOperands(const Matrix& matrix) const
{
	if (this->getRowSize() != matrix.getRowSize() || this->getColumnSize() != matrix.getColumnSize())
		throw
		std::logic_error(messages::OPERANDS_EQUAL);
}

void Matrix::validateResponse(Matrix& resp) const
{
	if (this->getRowSize() != resp.getRowSize() || this->getColumnSize() != resp.getColumnSize())
		throw
		std::logic_error(messages::NONCOMPT_RESP);
}

void Matrix::validateIndex(const unsigned int& rowIndex, const unsigned int& columnIndex) const
{
	if (rowIndex >= this->getRowSize() || columnIndex >= this->getColumnSize())
		throw std::logic_error(
			messages::INDEX_OUT);
}

void Matrix::validateOperandMult(const Matrix& matrix) const
{
	if (this->getColumnSize() != matrix.getRowSize()) throw std::logic_error(messages::OPERANDS_MAT_PROD);
}

void Matrix::validateResponseMult(const Matrix& matrix, const Matrix& resp) const
{
	if (this->getRowSize() != resp.getRowSize() || matrix.getColumnSize() != resp.getColumnSize())
		throw
		std::logic_error(messages::OPERANDS_MAT_PROD);
}

void Matrix::validateVectorMult(const Vector& vector) const
{
	if (this->getColumnSize() != vector.getSize()) throw std::logic_error(messages::OPERANDS_MAT_PROD);
}

void Matrix::validateVectorRespMult(Vector& resp) const
{
	if (this->getRowSize() != resp.getSize()) throw std::logic_error(messages::NONCOMPT_RESP);
}
