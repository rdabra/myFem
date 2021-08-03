#include "pch.h"
#include "MatrixSymmetric.h"


MatrixSymmetric::MatrixSymmetric(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matTri.reset(size, true);
}

MatrixSymmetric::MatrixSymmetric(const MatrixSymmetric& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = matrix._matTri;
}

MatrixSymmetric::MatrixSymmetric(MatrixSymmetric&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_matTri = std::move(matrix._matTri);
	matrix.~MatrixSymmetric();
}

double MatrixSymmetric::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	return (columnIndex > rowIndex) ? _matTri(columnIndex, rowIndex) : _matTri(rowIndex, columnIndex);
}


MatrixSymmetric& MatrixSymmetric::operator=(const MatrixSymmetric& matrix)
{
	if (!(this == &matrix)) {
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_matTri = matrix._matTri;
	}

	return (*this);
}

MatrixSymmetric& MatrixSymmetric::operator=(MatrixSymmetric&& matrix) noexcept
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = std::move(matrix._matTri);

	matrix.~MatrixSymmetric();

	return (*this);
}

MatrixSymmetric MatrixSymmetric::operator+(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(this->getRowSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSymmetric MatrixSymmetric::operator-(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(this->getRowSize());
	this->minus(matrix, resp);

	return resp;
}

MatrixSymmetric MatrixSymmetric::operator*(const double& scalar) const
{
	MatrixSymmetric resp(this->getSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) * scalar, i, j);

	return resp;
}
