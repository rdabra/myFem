#include "pch.h"

#include "Matrix.h"

/**
 * @brief Constructs the object by specifying dimensions
 * @param rowSize    Row size 
 * @param columnSize Column size
*/
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
	_matrix = std::move(matrix._matrix);


	matrix.~Matrix();
}

/**
 * @brief Resets the object to initial settings           
 * @param rowSize    Row size
 * @param columnSize Column size
*/
void Matrix::reset(const unsigned& rowSize, const unsigned& columnSize)
{
	_matrix.clear();
	_rowSize = rowSize;
	_columnSize = columnSize;
	_matrix.resize(this->Matrix::getVectorSize());
}

/**
 * @brief Returns an element value
 * @param rowIndex    Row index
 * @param columnIndex Column index
 * @return Element value
 * @exception std::logic_error Parameters out of bounds
*/
double Matrix::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	this->validateIndex(rowIndex, columnIndex);
	return _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

/**
 * @brief Sets a value for an element
 * @param value       Value to be set
 * @param rowIndex    Row index
 * @param columnIndex Column index
 * @exception std::logic_error Parameters out of bounds
*/
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

	matrix.~Matrix();
	return (*this);
}

bool Matrix::operator==(const Matrix& matrix) const
{
	const bool test{this->getRowSize() == matrix.getRowSize() && this->getColumnSize() == matrix.getColumnSize()};

	if (test) {
		for (unsigned i = 0; i < this->getRowSize(); i++)
			for (unsigned j = 0; j < this->getColumnSize(); j++)
				if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;

	}
	else return false;

	return true;
}

/**
 * @brief Calculates the dot product of this matrix with the parameter
 * @param matrix The right operand
 * @details The dot product of \f$ A\f$ and \f$ B\f$ is 
 *  \f[
 *		A:B = \sum_{i,j}A_{ij}B_{ij}	
 *  \f]
 * @return The result of the dot product
 * @exception std::logic_error Operands are not compatible 
*/
double Matrix::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			resp += (*this)(i, j) * matrix(i, j);

	return resp;
}

/**
 * @brief Calculates the sum of this matrix with the first parameter
 * @param matrix The right operand
 * @param resp  The result of the sum
 * @exception std::logic_error Parameters are not compatible
*/
void Matrix::plus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) + matrix(i, j), i, j);
}


/**
 * @brief Calculates the sum of this matrix with the parameter
 * @param matrix The right operand
 * @return The result of the sum
 * @exception std::logic_error Parameters are not compatible
*/
Matrix Matrix::operator+(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());
	this->plus(matrix, resp);

	return resp;
}

/**
 * @brief Sums the parameter to this matrix 
 * @param matrix Parameter summed to this matrix
 * @exception std::logic_error Parameter is not compatible
*/
void Matrix::addBy(const Matrix& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

/**
 * @brief Calculates the subtraction between this matrix and the first parameter
 * @param matrix The right operand
 * @param resp  The result of the subtraction
 * @exception std::logic_error Parameters are not compatible
*/
void Matrix::minus(const Matrix& matrix, Matrix& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) - matrix(i, j), i, j);
}

/**
 * @brief Calculates the subtraction between this matrix and the parameter
 * @param matrix The right operand
 * @return The result of the subtraction
 * @exception std::logic_error Parameters are not compatible
*/
Matrix Matrix::operator-(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());

	this->minus(matrix, resp);

	return resp;
}

/**
 * @brief Subtracts the parameter from this matrix
 * @param matrix Parameter that subtracts this matrix
 * @exception std::logic_error Parameter is not compatible
*/
void Matrix::subtractBy(const Matrix& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) - matrix(i, j), i, j);
}


/**
 * @brief Calculates the multiplication of this matrix and the first parameter
 * @param matrix The right operand
 * @param resp  The result of the multiplication
 * @exception std::logic_error Parameters are not compatible
*/
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


/**
 * @brief Calculates the multiplication of this matrix and the parameter
 * @param matrix The right operand
 * @return The result of the multiplication
 * @exception std::logic_error Parameters are not compatible
*/
Matrix Matrix::operator*(const Matrix& matrix) const
{
	Matrix resp(this->getRowSize(), matrix.getColumnSize());
	this->times(matrix, resp);

	return resp;
}

/**
 * @brief Calculates the multiplication of this matrix and the first parameter
 * @param vector The right operand
 * @param resp  The result of the multiplication
 * @exception std::logic_error Parameters are not compatible
*/
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

/**
 * @brief Calculates the multiplication of this matrix and the parameter
 * @param vector The right operand
 * @return The result of the multiplication
 * @exception std::logic_error Parameters are not compatible
*/
Vector Matrix::operator*(const Vector& vector) const
{
	Vector resp(this->getRowSize());
	this->times(vector, resp);

	return resp;
}

/**
 * @brief Calculates the multiplication of this matrix and the first parameter
 * @param scalar The right operand
 * @param resp  The result of the multiplication
 * @exception std::logic_error Parameters are not compatible
*/
void Matrix::times(const double& scalar, Matrix& resp) const
{
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			resp.setValue((*this)(i, j) * scalar, i, j);
}

/**
 * @brief Calculates the multiplication of this matrix and the parameter
 * @param scalar The right operand
 * @return The result of the multiplication
*/
Matrix Matrix::operator*(const double& scalar) const
{
	Matrix resp(this->getRowSize(), this->getColumnSize());
	this->times(scalar, resp);

	return resp;
}

/**
 * @brief Multiplies this matrix by the parameter
 * @param scalar Parameter that multiplies this matrix
 * @exception std::logic_error Parameter is not compatible
*/
void Matrix::multiplyBy(const double& scalar)
{
	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j < this->getColumnSize(); j++)
			this->setValue((*this)(i, j) * scalar, i, j);
}

/**
 * @brief Multiplies a specific row by a scalar
 * @param rowIndex Index of the row to be multiplied
 * @param scalar Parameter that multiplies the row
 * @exception std::logic_error Index out of bounds
*/
void Matrix::multiplyRowBy(const unsigned& rowIndex, const double& scalar)
{
	this->validateIndex(rowIndex, 0);

	for (unsigned j = 0; j < this->getColumnSize(); j++)
		this->setValue((*this)(rowIndex, j) * scalar, rowIndex, j);
}


/**
 * @brief Multiplies a specific column by a scalar
 * @param columnIndex Index of the column to be multiplied
 * @param scalar Parameter that multiplies the column
 * @exception std::logic_error Index out of bounds
*/
void Matrix::multiplyColumnBy(const unsigned& columnIndex, const double& scalar)
{
	this->validateIndex(0, columnIndex);

	for (unsigned i = 0; i < this->getRowSize(); i++)
		this->setValue((*this)(i, columnIndex) * scalar, i, columnIndex);
}

/**
 * @brief Swaps corresponding elements of two rows of this matrix from an initial column index to a final column index
 * @param rowIndexA A row index
 * @param rowIndexB Another row index
 * @param startColumn Initial column index 
 * @param endColumn Final column index
 * @exception std::logic_error Index out of bounds
*/
void Matrix::partialSwapRows(const unsigned& rowIndexA, const unsigned& rowIndexB,
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

/**
 * @brief Swaps two rows of this matrix
 * @param rowIndexA A row index
 * @param rowIndexB Another row index
 * @exception std::logic_error Index out of bounds
*/
inline void Matrix::swapRows(const unsigned& rowIndexA, const unsigned& rowIndexB)
{
	this->partialSwapRows(rowIndexA, rowIndexB, 0, this->getColumnSize() - 1);
}

/**
 * @brief Swaps corresponding elements of two columns of this matrix from an initial row index to a final row index
 * @param columnIndexA A column index
 * @param columnIndexB Another column index
 * @param startRow Initial column index
 * @param endRow  Final column index
 * @exception std::logic_error Index out of bounds
*/
void Matrix::partialSwapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                const unsigned& startRow, const unsigned& endRow)
{
	this->validateIndex(0, columnIndexA);
	this->validateIndex(0, columnIndexB);
	if (startRow >= this->getRowSize() || endRow >= this->getRowSize()) throw std::logic_error(messages::INDEX_OUT);

	for (unsigned i = startRow; i <= endRow; i++)
		_matrix[this->getVectorIndex(i, columnIndexB)] = std::exchange(_matrix[this->getVectorIndex(i, columnIndexA)],
		                                                               _matrix[this->getVectorIndex(i, columnIndexB)]);
}


/**
 * @brief Swaps two columns of this matrix
 * @param columnIndexA A column index
 * @param columnIndexB Another column index
*/
void Matrix::swapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB)
{
	this->partialSwapColumns(columnIndexA, columnIndexB, 0, this->getRowSize() - 1);
}


/**
 * @brief Transposes this matrix
*/
void Matrix::transpose()
{
	_isTransposed = !_isTransposed;
	std::swap(_rowSize, _columnSize);
}

/**
 * @brief Calculates the Frobenius Norm of this matrix
 * @details Frobenius Norm of matrix \f$ A\f$ is calculated from the dot product the following way:
 *  \f[
 *		\sqrt{A:A}	
 *  \f]
 * @return The value of the Frobenius Norm
*/
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
