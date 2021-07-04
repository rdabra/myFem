#include "pch.h"
#include "MatrixTriangular.h"

MatrixTriangular::MatrixTriangular(const unsigned int& size, bool isLower)
{
	_rowSize = size;
	_columnSize = size;
	_isLower = isLower;
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++)
		_matrix[i] = new double[i + (int64_t)1];
}

MatrixTriangular::MatrixTriangular(const MatrixTriangular& matrix)
{

	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_isLower = matrix.isLower();
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++) {
		_matrix[i] = new double[i + (int64_t)1];
		if (_isLower)
			for (unsigned int j = 0; j <= i; j++)
				_matrix[i][j] = matrix(i, j);
		else
			for (unsigned int j = i; j < _rowSize; j++)
				_matrix[j][i] = matrix(i, j);
	}
}


const double& MatrixTriangular::operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const
{
	Matrix::validadeIndex(rowIndex, columnIndex);

	bool isZero = (_isLower && columnIndex > rowIndex) || ((!_isLower) && columnIndex < rowIndex);

	return isZero ? putils::ZERO : _isLower ? _matrix[rowIndex][columnIndex] : _matrix[columnIndex][rowIndex];
}

void MatrixTriangular::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	Matrix::validadeIndex(rowIndex, columnIndex);
	if (_isLower) {
		if (columnIndex > rowIndex) throw std::out_of_range(messages::INDEX_OUT);
		_matrix[rowIndex][columnIndex] = value;
	}
	else
	{
		if (columnIndex < rowIndex) throw std::out_of_range(messages::INDEX_OUT);
		_matrix[columnIndex][rowIndex] = value;
	}
}


MatrixTriangular& MatrixTriangular::operator=(const MatrixTriangular& matrix)
{

	for (unsigned int i = 0; i < _rowSize; i++)
		delete[] _matrix[i];
	delete[] _matrix;
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_isLower = matrix.isLower();
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++) {
		_matrix[i] = new double[i + (int64_t)1];
		if (_isLower)
			for (unsigned int j = 0; j <= i; j++)
				_matrix[i][j] = matrix(i, j);
		else
			for (unsigned int j = i; j < _rowSize; j++)
				_matrix[j][i] = matrix(i, j);
	}
	return (*this);
}

MatrixTriangular& MatrixTriangular::operator=(MatrixTriangular&& matrix) noexcept
{
	for (unsigned int i = 0; i < _rowSize; i++)
		delete[] _matrix[i];
	delete[] _matrix;
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_isLower = matrix.isLower();
	_matrix = std::exchange(matrix._matrix, nullptr);

	return (*this);
}

double MatrixTriangular::dotProduct(const MatrixSquare& matrix) const
{
	this->validateOperands(matrix);

	double resp = 0.0;
	if (this->isLower())
		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				resp += (*this)(i, j) * matrix(i, j);
	else
		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = i; j < this->getColumnSize(); j++)
				resp += (*this)(i, j) * matrix(i, j);

	return resp;
}

void MatrixTriangular::plus(const MatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validadeResponse(resp);

	if (_isLower == matrix.isLower()) {
		if (this->isLower())
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
					resp.setValue((*this)(i, j) + matrix(i, j), i, j);
		else
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = i; j < this->getColumnSize(); j++)
					resp.setValue((*this)(i, j) + matrix(i, j), i, j);
	}
	else {
		if (this->isLower())
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) + matrix(i, i), i, i);
					else {
						resp.setValue((*this)(i, j), i, j);
						resp.setValue(matrix(j, i), j, i);
					}
		else
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
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
	if (_isLower != matrix.isLower())
		throw std::out_of_range(messages::NONCOMPT_ARG);

	if (this->isLower())
		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				this->setValue((*this)(i, j) + matrix(i, j), i, j);
	else
		for (unsigned int i = 0; i < this->getRowSize(); i++)
			for (unsigned int j = i; j < this->getColumnSize(); j++)
				this->setValue((*this)(i, j) + matrix(i, j), i, j);
}

void MatrixTriangular::minus(const MatrixTriangular& matrix, MatrixSquare& resp) const
{
	this->validateOperands(matrix);
	this->validadeResponse(resp);

	if (_isLower == matrix.isLower()) {
		if (this->isLower())
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
					resp.setValue((*this)(i, j) - matrix(i, j), i, j);
		else
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = i; j < this->getColumnSize(); j++)
					resp.setValue((*this)(i, j) - matrix(i, j), i, j);
	}
	else {
		if (this->isLower())
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) - matrix(i, i), i, i);
					else {
						resp.setValue((*this)(i, j), i, j);
						resp.setValue(matrix(j, i), j, i);
					}
		else
			for (unsigned int i = 0; i < this->getRowSize(); i++)
				for (unsigned int j = 0; j <= i; j++)
					if (i == j)
						resp.setValue((*this)(i, i) - matrix(i, i), i, i);
					else {
						resp.setValue((*this)(j, i), j, i);
						resp.setValue(matrix(i, j), i, j);
					}
	}
}

void MatrixTriangular::subtractBy(const MatrixTriangular& matrix)
{
	if (_isLower != matrix.isLower())
		throw std::out_of_range(messages::NONCOMPT_ARG);

	if (this->isLower())
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				this->setValue((*this)(i, j) - matrix(i, j), i, j);
	else
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = i; j < this->getSize(); j++)
				this->setValue((*this)(i, j) - matrix(i, j), i, j);
}

void MatrixTriangular::times(const MatrixSquare& matrix, MatrixSquare& resp) const
{
	this->validadeOperandMult(matrix);
	this->validadeResponseMult(matrix, resp);

	if (this->isLower()) {
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= this->getSize(); j++)
			{
				double aux = 0.0;
				for (unsigned int k = 0; k <= i; k++)
					aux += (*this)(i, k) * matrix(k, j);
				resp.setValue(aux, i, j);
			}
	}
	else {
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= this->getSize(); j++)
			{
				double aux = 0.0;
				for (unsigned int k = i; k <= this->getSize(); k++)
					aux += (*this)(i, k) * matrix(k, j);
				resp.setValue(aux, i, j);
			}
	}

}

void MatrixTriangular::multiplyBy(const double& scalar)
{
	if (this->isLower())
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				this->setValue((*this)(i, j) * scalar, i, j);
	else
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = i; j < this->getSize(); j++)
				this->setValue((*this)(i, j) * scalar, i, j);
}

double MatrixTriangular::frobeniusNorm() const
{
	double resp = 0.0;

	if (this->isLower())
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				resp += (*this)(i, j) * (*this)(i, j);
	else
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j < this->getSize(); j++)
				resp += (*this)(i, j) * (*this)(i, j);


	return sqrt(resp);
}

void MatrixTriangular::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator
	std::mt19937 rng;

	//Initialize with non-deterministic seeds
	rng.seed(std::random_device{}());

	if (this->isLower())
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = 0; j <= i; j++)
				this->setValue(dist(rng), i, j);
	else
		for (unsigned int i = 0; i < this->getSize(); i++)
			for (unsigned int j = i + 1; j < this->getSize(); j++)
				this->setValue(dist(rng), i, j);
}

double MatrixTriangular::determinant() const
{
	double resp = 1.0;

	for (unsigned int i = 0; i < this->getSize(); i++)
		resp *= (*this)(i, i);

	return resp;
}


