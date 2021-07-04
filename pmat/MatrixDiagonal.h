#pragma once
#include "MatrixSquare.h"

class MatrixDiagonal :
	public MatrixSquare
{
public:
	MatrixDiagonal(const unsigned int& size);
	MatrixDiagonal(const MatrixDiagonal& matrix);
	MatrixDiagonal(MatrixDiagonal&& matrix) noexcept : MatrixSquare(matrix) {};
	virtual ~MatrixDiagonal() {};
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	MatrixDiagonal& operator=(const MatrixDiagonal& matrix);
	double dotProduct(const Matrix& matrix) const;
	void plus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	virtual void addBy(const MatrixDiagonal& matrix);
	void minus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	virtual void subtractBy(const MatrixDiagonal& matrix);
	void times(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	void times(const Vector& vector, Vector& resp) const;
	void times(const double& scalar, MatrixDiagonal& resp) const;
	virtual void multiplyBy(const double& scalar);
	virtual double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	virtual double determinant() const;

};

