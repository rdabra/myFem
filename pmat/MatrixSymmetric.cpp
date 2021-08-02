#include "pch.h"
#include "MatrixSymmetric.h"


MatrixSymmetric::MatrixSymmetric(const unsigned& size, bool antiSymmetric)
{
	_rowSize = size;
	_columnSize = size;
	_antiSymmetric = antiSymmetric;
	_matTri.reset(size, true);
}

MatrixSymmetric::MatrixSymmetric(const MatrixSymmetric& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_antiSymmetric = matrix.isAntiSymmetric();
	_matTri = matrix._matTri;
}

MatrixSymmetric::MatrixSymmetric(MatrixSymmetric&& matrix) noexcept
{
	_rowSize = matrix._rowSize;
	_columnSize = matrix._columnSize;
	_antiSymmetric = matrix.isAntiSymmetric();
	_matTri = std::move(matrix._matTri);
	matrix.~MatrixSymmetric();
}

double MatrixSymmetric::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	return (columnIndex > rowIndex)
		       ? this->isAntiSymmetric()
			         ? putils::MINUS_ONE * _matTri(columnIndex, rowIndex)
			         : _matTri(columnIndex, rowIndex)
		       : _matTri(rowIndex, columnIndex);
}

void MatrixSymmetric::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	_matTri.setValue(value, rowIndex, columnIndex);
}

void MatrixSymmetric::reset(const unsigned& size, bool antiSymmetric)
{
	_rowSize = size;
	_columnSize = size;
	_antiSymmetric = antiSymmetric;
	_matTri.reset(size, true);
}

bool MatrixSymmetric::operator==(MatrixSymmetric& matrix) const
{
	return _matTri == matrix._matTri;
}

MatrixSymmetric& MatrixSymmetric::operator=(const MatrixSymmetric& matrix)
{
	if (!(this == &matrix)) {
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_antiSymmetric = matrix.isAntiSymmetric();
		_matTri = matrix._matTri;
	}

	return (*this);
}

MatrixSymmetric& MatrixSymmetric::operator=(MatrixSymmetric&& matrix) noexcept
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_antiSymmetric = matrix.isAntiSymmetric();
	_matTri = std::move(matrix._matTri);

	matrix.~MatrixSymmetric();

	return (*this);
}

double MatrixSymmetric::dotProduct(const MatrixSymmetric& matrix) const
{
	this->validateOperands(matrix);
	double resp{0.0};
	for (unsigned i = 0; i < this->getSize(); i++) {
		for (unsigned j = 0; j < i; j++)
			resp += 2.0 * (*this)(i, j) * matrix(i, j);
		resp += (*this)(i, i) * matrix(i, i);
	}

	return resp;
}

void MatrixSymmetric::plus(const MatrixSymmetric& matrix, MatrixSymmetric& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) + matrix(i, j), i, j);
}

void MatrixSymmetric::addBy(const MatrixSymmetric& matrix)
{
	_matTri.addBy(matrix._matTri);
}

void MatrixSymmetric::minus(const MatrixSymmetric& matrix, MatrixSymmetric& resp) const
{
	this->validateOperands(matrix);
	this->validateResponse(resp);

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) - matrix(i, j), i, j);
}

MatrixSymmetric MatrixSymmetric::operator+(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(matrix.getSize(), matrix.isAntiSymmetric());
	this->plus(matrix, resp);

	return resp;
}

MatrixSymmetric MatrixSymmetric::operator-(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(matrix.getSize(), matrix.isAntiSymmetric());
	this->minus(matrix, resp);

	return resp;
}

void MatrixSymmetric::subtractBy(const MatrixSymmetric& matrix)
{
	_matTri.subtractBy(matrix._matTri);
}

void MatrixSymmetric::multiplyBy(const double& scalar)
{
	_matTri.multiplyBy(scalar);
}

MatrixSymmetric MatrixSymmetric::operator*(const double& scalar) const
{
	MatrixSymmetric resp(this->getSize(), this->isAntiSymmetric());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) * scalar, i, j);

	return resp;
}

double MatrixSymmetric::frobeniusNorm() const
{
	return std::sqrt(this->dotProduct((*this)));
}
