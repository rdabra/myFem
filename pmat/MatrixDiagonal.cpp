#include "pch.h"
#include "MatrixDiagonal.h"

MatrixDiagonal::MatrixDiagonal(const unsigned int& size)
{
	_rowSize = size;
	_columnSize = size;
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++)
		_matrix[i] = new double[1];
}

MatrixDiagonal::MatrixDiagonal(const MatrixDiagonal& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++) {
		_matrix[i] = new double[1];
		_matrix[i][0] = matrix(i, i);
	}
}


void MatrixDiagonal::setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex)
{
	Matrix::validadeIndex(rowIndex, columnIndex);

	if (columnIndex != rowIndex) throw std::out_of_range(messages::INDEX_OUT);

	_matrix[rowIndex][0] = value;
}

const double& MatrixDiagonal::operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const
{
	Matrix::validadeIndex(rowIndex, columnIndex);

	return rowIndex != columnIndex ? putils::ZERO : _matrix[rowIndex][0];
}

MatrixDiagonal& MatrixDiagonal::operator=(const MatrixDiagonal& matrix)
{
	for (unsigned int i = 0; i < _rowSize; i++)
		delete[] _matrix[i];
	delete[] _matrix;

	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matrix = new double* [_rowSize];
	for (unsigned int i = 0; i < _rowSize; i++) {
		_matrix[i] = new double[1];
		_matrix[i][0] = matrix(i, i);
	}

	return (*this);
}
