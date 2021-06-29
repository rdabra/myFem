#pragma once
#include "MatrixSquare.h"

class MatrixDiagonal :
    public MatrixSquare
{
public:
	MatrixDiagonal(const unsigned int& size);
	MatrixDiagonal(const MatrixDiagonal& matrix);
	virtual ~MatrixDiagonal() {};
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	MatrixDiagonal& operator=(const MatrixDiagonal& matrix);
	virtual void addBy(const MatrixDiagonal& matrix);
	virtual void subtractBy(const MatrixDiagonal& matrix);
	virtual void multiplyBy(const double& scalar);
	virtual double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	virtual double determinant() const;

};

