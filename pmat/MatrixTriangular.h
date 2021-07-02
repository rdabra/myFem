#pragma once

#include "MatrixSquare.h"

class MatrixTriangular : public MatrixSquare
{

private:
	bool _isLower;

public:
	MatrixTriangular(const unsigned int& size, bool isLower);
	MatrixTriangular(const MatrixTriangular& matrix);
	MatrixTriangular(MatrixTriangular&& matrix) noexcept : MatrixTriangular(matrix) { _isLower = matrix._isLower; };
	virtual ~MatrixTriangular() {};
	inline const bool& isLower() const { return _isLower; };
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	MatrixTriangular& operator=(const MatrixTriangular& matrix);
	MatrixTriangular& operator=(MatrixTriangular&& matrix) noexcept;
	virtual void addBy(const MatrixTriangular& matrix);
	virtual void subtractBy(const MatrixTriangular& matrix);
	virtual void multiplyBy(const double& scalar);
	virtual double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	virtual double determinant() const;
};
