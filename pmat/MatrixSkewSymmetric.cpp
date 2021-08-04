#include "pch.h"
#include "MatrixSkewSymmetric.h"


MatrixSkewSymmetric::MatrixSkewSymmetric(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matTri.reset(size, true);
}

MatrixSkewSymmetric::MatrixSkewSymmetric(const MatrixSkewSymmetric& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = matrix._matTri;
}

MatrixSkewSymmetric::MatrixSkewSymmetric(MatrixSkewSymmetric&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_matTri = std::move(matrix._matTri);
	matrix.~MatrixSkewSymmetric();
}

double MatrixSkewSymmetric::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	return (columnIndex > rowIndex)
		       ? putils::MINUS_ONE * _matTri(columnIndex, rowIndex)
		       : _matTri(rowIndex, columnIndex);
}


MatrixSkewSymmetric& MatrixSkewSymmetric::operator=(const MatrixSkewSymmetric& matrix)
{
	if (!(this == &matrix)) {
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_matTri = matrix._matTri;
	}

	return (*this);
}

MatrixSkewSymmetric& MatrixSkewSymmetric::operator=(MatrixSkewSymmetric&& matrix) noexcept
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = std::move(matrix._matTri);

	matrix.~MatrixSkewSymmetric();

	return (*this);
}

MatrixSkewSymmetric MatrixSkewSymmetric::operator+(const MatrixSkewSymmetric& matrix) const
{
	MatrixSkewSymmetric resp(this->getRowSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSkewSymmetric MatrixSkewSymmetric::operator-(const MatrixSkewSymmetric& matrix) const
{
	MatrixSkewSymmetric resp(this->getRowSize());
	this->minus(matrix, resp);

	return resp;
}

MatrixSkewSymmetric MatrixSkewSymmetric::operator*(const double& scalar) const
{
	MatrixSkewSymmetric resp(this->getSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) * scalar, i, j);

	return resp;
}

void MatrixSkewSymmetric::transpose()
{
	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			this->setValue((*this)(i, j) * putils::MINUS_ONE, i, j);
}
