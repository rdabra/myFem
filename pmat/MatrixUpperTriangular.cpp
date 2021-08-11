#include "pch.h"
#include "MatrixUpperTriangular.h"

MatrixUpperTriangular::MatrixUpperTriangular(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matrix.resize(this->AbstractMatrixTriangular::getVectorSize());
}

MatrixUpperTriangular::MatrixUpperTriangular(const MatrixUpperTriangular& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix.resize(matrix.getVectorSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->AbstractMatrixTriangular::setValue(matrix(i, j), i, j);
}

MatrixUpperTriangular::MatrixUpperTriangular(MatrixUpperTriangular&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_matrix = std::move(matrix._matrix);
	matrix.~MatrixUpperTriangular();
}

void MatrixUpperTriangular::reset(const unsigned& size)
{
	_matrix.clear();
	_rowSize = size;
	_columnSize = size;
	_matrix.resize(this->getVectorSize());
}

void MatrixUpperTriangular::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	if (columnIndex < rowIndex)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::setValue(value, rowIndex, columnIndex);
}

double MatrixUpperTriangular::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	validateIndex(rowIndex, columnIndex);

	return columnIndex < rowIndex ? putils::ZERO : _matrix[this->getVectorIndex(rowIndex, columnIndex)];
}

bool MatrixUpperTriangular::operator==(const MatrixUpperTriangular& matrix) const
{
	if (this->getSize() != matrix.getSize()) return false;

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++) {
			if (!putils::areEqual((*this)(i, j), matrix(i, j))) return false;
		}

	return true;
}

MatrixUpperTriangular& MatrixUpperTriangular::operator=(const MatrixUpperTriangular& matrix)
{
	if (!(this == &matrix)) {
		_matrix.clear();
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_matrix.resize(matrix.getVectorSize());
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				this->setValue(matrix(i, j), i, j);
	}

	return (*this);
}

MatrixUpperTriangular& MatrixUpperTriangular::operator=(MatrixUpperTriangular&& matrix) noexcept
{
	_matrix.clear();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix = std::move(matrix._matrix);

	matrix.~MatrixUpperTriangular();

	return (*this);
}

double MatrixUpperTriangular::dotProduct(const Matrix& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++)
			resp += (*this)(i, j) * matrix(i, j);

	return resp;
}


void MatrixUpperTriangular::plus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (!matrix.isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				resp.setValue((*this)(i, j) + matrix(i, j), i, j);
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

void MatrixUpperTriangular::addBy(const MatrixUpperTriangular& matrix)
{
	this->validateOperands(matrix);


	for (unsigned i = 0; i < this->getRowSize(); i++)
		for (unsigned j = i; j < this->getRowSize(); j++)
			this->setValue((*this)(i, j) + matrix(i, j), i, j);
}


void MatrixUpperTriangular::minus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	if (!matrix.isLower())
		for (unsigned i = 0; i < this->getSize(); i++)
			for (unsigned j = i; j < this->getSize(); j++)
				resp.setValue((*this)(i, j) - matrix(i, j), i, j);
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

void MatrixUpperTriangular::subtractBy(const MatrixUpperTriangular& matrix)
{
	this->validateOperands(matrix);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void MatrixUpperTriangular::times(const MatrixSquare& matrix, MatrixSquare& resp) const
{
	this->validateOperandMult(matrix);
	this->validateResponseMult(matrix, resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j < this->getSize(); j++) {
			double aux = putils::ZERO;
			for (unsigned k = i; k < this->getSize(); k++)
				aux += (*this)(i, k) * matrix(k, j);
			resp.setValue(aux, i, j);
		}
}

void MatrixUpperTriangular::times(const Vector& vector, Vector& resp) const
{
	this->validateVectorMult(vector);
	this->validateVectorRespMult(resp);

	for (unsigned i = 0; i < this->getSize(); i++) {
		double aux = putils::ZERO;
		for (unsigned k = i; k < this->getSize(); k++)
			aux += (*this)(i, k) * vector(k);
		resp.setValue(aux, i);
	}
}

void MatrixUpperTriangular::times(const double& scalar, MatrixUpperTriangular& resp) const
{
	this->validateOperands(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++)
			resp.setValue((*this)(i, j) * scalar, i, j);
}

void MatrixUpperTriangular::multiplyBy(const double& scalar)
{
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++)
			this->setValue((*this)(i, j) * scalar, i, j);
}

MatrixLowerTriangular MatrixUpperTriangular::getTranspose() const
{
	MatrixLowerTriangular resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(j, i), i, j);

	return resp;
}

void MatrixUpperTriangular::swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB,
                                            const unsigned& startColumn, const unsigned& endColumn)
{
	if (startColumn < rowIndexA || startColumn < rowIndexB)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::swapRowElements(rowIndexA, rowIndexB, startColumn, endColumn);
}

void MatrixUpperTriangular::swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
                                               const unsigned& startRow, const unsigned& endRow)
{
	if (endRow > columnIndexA || endRow > columnIndexB)
		throw std::out_of_range(messages::INDEX_OUT);

	AbstractMatrixTriangular::swapColumnElements(columnIndexA, columnIndexB, startRow, endRow);
}

void MatrixUpperTriangular::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = i; j < this->getSize(); j++)
			this->setValue(dist(rng), i, j);
}
