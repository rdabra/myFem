#pragma once
#include "MatrixSquare.h"
#include "MatrixTriangular.h"

class AbstractMatSymSkewSym :
	public MatrixSquare
{
private:
	std::vector<double> _matrix; // Changing visibility in order to prevent inheritance

protected:
	MatrixTriangular _matTri;

public:
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override = 0;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	void reset(const unsigned& size);
	bool operator==(AbstractMatSymSkewSym& matrix) const;
	void plus(const AbstractMatSymSkewSym& matrix, AbstractMatSymSkewSym& resp) const;
	virtual void addBy(const AbstractMatSymSkewSym& matrix);
	void addBy(const Matrix& matrix) override { Matrix::addBy(matrix); } 
	void minus(const AbstractMatSymSkewSym& matrix, AbstractMatSymSkewSym& resp) const;
	virtual void subtractBy(const AbstractMatSymSkewSym& matrix);
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void multiplyBy(const double& scalar) override;
	virtual MatrixSquare operator*(const AbstractMatSymSkewSym& matrix) const { return MatrixSquare::operator*(matrix); }
	double dotProduct(const AbstractMatSymSkewSym& matrix) const;
	double dotProduct(const Matrix& matrix) const override { return Matrix::dotProduct(matrix); }
	double frobeniusNorm() const override;
	void transpose() override = 0;

};

