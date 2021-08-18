#include "pch.h"
#include "MatrixLowerTriangular.h"


MatrixLowerTriangular::MatrixLowerTriangular(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matrix.resize(this->AbstractMatrixTriangular::getVectorSize());
}

MatrixLowerTriangular::MatrixLowerTriangular(const MatrixLowerTriangular& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix.resize(matrix.getVectorSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->AbstractMatrixTriangular::setValue(matrix(i, j), i, j);
}

MatrixLowerTriangular::MatrixLowerTriangular(MatrixLowerTriangular&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_matrix = std::move(matrix._matrix);
	matrix.~MatrixLowerTriangular();
}

void MatrixLowerTriangular::reset(const unsigned& size)
{
	_matrix.clear();
	_rowSize = size;
	_columnSize = size;
	_matrix.resize(this->getVectorSize());
}

void MatrixLowerTriangular::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	if (columnIndex > rowIndex)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::setValue(value, rowIndex, columnIndex);
}

double MatrixLowerTriangular::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	validateIndex(rowIndex, columnIndex);

	return columnIndex > rowIndex ? putils::ZERO : _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

bool MatrixLowerTriangular::operator==(const MatrixLowerTriangular& matrix) const
{
	if (this->getSize() != matrix.getSize()) return false;

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++) {
			if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;
		}

	return true;
}

MatrixLowerTriangular& MatrixLowerTriangular::operator=(const MatrixLowerTriangular& matrix)
{
	if (!(this == &matrix)) {
		_matrix.clear();
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_matrix.resize(matrix.getVectorSize());
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				this->setValue(matrix(i, j), i, j);
	}

	return (*this);
}

MatrixLowerTriangular& MatrixLowerTriangular::operator=(MatrixLowerTriangular&& matrix) noexcept
{
	_matrix.clear();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix = std::move(matrix._matrix);

	matrix.~MatrixLowerTriangular();

	return (*this);
}

double MatrixLowerTriangular::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp += (*this)(i, j) * matrix(i, j);

	return resp;
}


void MatrixLowerTriangular::plus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (matrix.isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				resp.setValue((*this)(i, j) + matrix(i, j), i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				if (i == j)
					resp.setValue((*this)(i, i) + matrix(i, i), i, i);
				else {
					resp.setValue((*this)(i, j), i, j);
					resp.setValue(matrix(j, i), j, i);
				}
}

void MatrixLowerTriangular::addBy(const MatrixLowerTriangular& matrix)
{
	this->validateOperands(matrix);


	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue((*this)(i, j) + matrix(i, j), i, j);
}


void MatrixLowerTriangular::minus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (matrix.isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				resp.setValue((*this)(i, j) - matrix(i, j), i, j);
	else
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = 0; j <= i; j++)
				if (i == j)
					resp.setValue((*this)(i, i) - matrix(i, i), i, i);
				else {
					resp.setValue((*this)(i, j), i, j);
					resp.setValue(-matrix(j, i), j, i);
				}
}

void MatrixLowerTriangular::subtractBy(const MatrixLowerTriangular& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void MatrixLowerTriangular::times(const MatrixSquare& matrix, MatrixSquare& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j < this->getSize(); j++) {
			double aux = putils::ZERO;
			for (unsigned k = 0; k <= i; k++)
				aux += (*this)(i, k) * matrix(k, j);
			resp.setValue(aux, i, j);
		}
}

void MatrixLowerTriangular::times(const Vector& vector, Vector& resp) const
{
	this->validateVectorMult(vector);
	this->validateVectorRespMult(resp);

	for (unsigned i = 0; i < this->getSize(); i++) {
		double aux = 0.0;
		for (unsigned k = 0; k <= i; k++)
			aux += (*this)(i, k) * vector(k);
		resp.setValue(aux, i);
	}
}

void MatrixLowerTriangular::times(const double& scalar, MatrixLowerTriangular& resp) const
{
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) * scalar, i, j);
}

void MatrixLowerTriangular::multiplyBy(const double& scalar)
{
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue((*this)(i, j) * scalar, i, j);
}

MatrixLowerTriangular MatrixLowerTriangular::operator*(const double& scalar) const
{
	MatrixLowerTriangular resp(this->getSize());
	this->times(scalar, resp);

	return resp;
}

/**
 * @return The transposed matrix of this matrix
*/
MatrixUpperTriangular MatrixLowerTriangular::getTranspose() const
{
	MatrixUpperTriangular resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++)
			resp.setValue((*this)(j, i), i, j);
	return resp;
}

void MatrixLowerTriangular::partialSwapRows(const unsigned& rowIndexA, const unsigned& rowIndexB,
                                            const unsigned& startColumn, const unsigned& endColumn)
{
	if (endColumn > rowIndexA || endColumn > rowIndexB)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::partialSwapRows(rowIndexA, rowIndexB, startColumn, endColumn);
}

void MatrixLowerTriangular::partialSwapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                               const unsigned& startRow, const unsigned& endRow)
{
	if (columnIndexA > startRow || columnIndexB > startRow)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::partialSwapColumns(columnIndexA, columnIndexB, startRow, endRow);
}

void MatrixLowerTriangular::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue(dist(rng), i, j);
}

MatrixSquare MatrixLowerTriangular::getInverse()
{
	return this->getInverseAsLowerTriangular().toMatrixSquare();
}

MatrixLowerTriangular MatrixLowerTriangular::getInverseAsLowerTriangular()
{
	MatrixLowerTriangular resp(this->getSize());
	this->findInverseByBackSubstitution(this, &resp);
	return resp;
}

void MatrixLowerTriangular::copyElementsFrom(const MatrixLowerTriangular& matrix)
{
	this->validateOperands(matrix);
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <=i ; j++)
			this->setValue(matrix(i, j), i, j);
}
