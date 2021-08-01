#include "pch.h"

#include "Matrix.h"

Matrix::Matrix(const unsigned& rowSize, const unsigned& columnSize)
{
	_rowSize = rowSize;
	_columnSize = columnSize;
	_matrix.resize(this->Matrix::getVectorSize());
}

Matrix::Matrix(const Matrix& matrix)
{
	_rowSize = matrix.getRowSize();
	_columnSize = matrix.getColumnSize();
	_matrix.resize(matrix.getVectorSize());

	for (unsigned i = 0; i < this->Matrix::getRowSize(); i++)
		for (unsigned j = 0; j < this->Matrix::getColumnSize(); j++)
			this->Matrix::setValue(matrix(i, j), i, j);
}

Matrix::Matrix(Matrix&& matrix) noexcept
{
	_rowSize = matrix.getRowSize();
	_columnSize = matrix.getColumnSize();
	_matrix.resize(this->Matrix::getVectorSize());

	for (unsigned i = 0; i < this->Matrix::getRowSize(); i++)
		for (unsigned j = 0; j < this->Matrix::getColumnSize(); j++)
			this->Matrix::setValue(matrix(i, j), i, j);

	matrix.~Matrix();
}

const double& Matrix::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	this->validateIndex(rowIndex, columnIndex);
	return _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

void Matrix::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
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

		for (unsigned i = 0; i < this->getRowSize(); i++)
			for (unsigned j = 0; j < this->getColumnSize(); j++)
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
	bool test{this->getRowSize() == matrix.getRowSize() && this->getColumnSize() == matrix.getColumnSize()};

	if (test) {
		for (unsigned i = 0; i < this->getRowSize(); i++)
			for (unsigned j = 0; j < this->getColumnSize(); j++)
				if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;

	}
	else return false;

	return true;
}

double Matrix::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			resp += (*this)(i, j) * matrix(i, j);

	return resp;
}

void Matrix::plus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
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

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

void Matrix::minus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
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

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void Matrix::times(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < matrix.getColumnSize(); j++) {
			double aux = 0.0;
			for (unsigned k = 0; k < this->getColumnSize(); k++)
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

	for (unsigned i = 0; i < this->getRowSize(); i++) {
		double aux = 0.0;
		for (unsigned k = 0; k < this->getColumnSize(); k++)
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
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
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
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) * scalar, i, j);
}

void Matrix::multiplyRowBy(const unsigned& rowIndex, const double& scalar)
{
	this->validateIndex(rowIndex, 0);

	for (unsigned j = 0; j < this->getColumnSize(); j++)
		this->setValue((*this)(rowIndex, j) * scalar, rowIndex, j);
}

void Matrix::multiplyColumnBy(const unsigned& columnIndex, const double& scalar)
{
	this->validateIndex(0, columnIndex);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, columnIndex) * scalar, i, columnIndex);
}

void Matrix::swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB,
                             const unsigned& startColumn, const unsigned& endColumn)
{
	this->validateIndex(rowIndexA, 0);
	this->validateIndex(rowIndexB, 0);
	if (startColumn >= this->getColumnSize() || endColumn >= this->getColumnSize())
		throw std::logic_error(
			messages::INDEX_OUT);

	for (unsigned j = startColumn; j <= endColumn; j++)
		_matrix[this->getVectorIndex(rowIndexB, j)] = std::exchange(_matrix[this->getVectorIndex(rowIndexA, j)],
		                                                            _matrix[this->getVectorIndex(rowIndexB, j)]);
}

inline void Matrix::swapRows(const unsigned& rowIndexA, const unsigned& rowIndexB)
{
	this->swapRowElements(rowIndexA, rowIndexB, 0, this->getColumnSize() - 1);
}

void Matrix::swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                const unsigned& startRow, const unsigned& endRow)
{
	this->validateIndex(0, columnIndexA);
	this->validateIndex(0, columnIndexB);
	if (startRow >= this->getRowSize() || endRow >= this->getRowSize()) throw std::logic_error(messages::INDEX_OUT);

	for (unsigned i = startRow; i <= endRow; i++)
		_matrix[this->getVectorIndex(i, columnIndexB)] = std::exchange(_matrix[this->getVectorIndex(i, columnIndexA)],
		                                                               _matrix[this->getVectorIndex(i, columnIndexB)]);
}


void Matrix::swapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB)
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
	return sqrt(this->dotProduct((*this)));
}

void Matrix::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
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

void Matrix::validateIndex(const unsigned& rowIndex, const unsigned& columnIndex) const
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
