#pragma once
#include "MatrixSquare.h"
#include "MatrixLowerTriangular.h"

class AbstractMatrixSymmetry :
	public MatrixSquare
{
private:
	std::vector<double> _matrix; // Changing visibility in order to prevent inheritance

protected:
	MatrixLowerTriangular _matTri;

public:
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override = 0;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	void reset(const unsigned& size);
	bool operator==(AbstractMatrixSymmetry& matrix) const;
	void plus(const AbstractMatrixSymmetry& matrix, AbstractMatrixSymmetry& resp) const;
	virtual void addBy(const AbstractMatrixSymmetry& matrix);
	void addBy(const Matrix& matrix) override { Matrix::addBy(matrix); } 
	void minus(const AbstractMatrixSymmetry& matrix, AbstractMatrixSymmetry& resp) const;
	virtual void subtractBy(const AbstractMatrixSymmetry& matrix);
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void multiplyBy(const double& scalar) override;
	virtual MatrixSquare operator*(const AbstractMatrixSymmetry& matrix) const { return MatrixSquare::operator*(matrix); }
	double dotProduct(const AbstractMatrixSymmetry& matrix) const;
	double dotProduct(const Matrix& matrix) const override { return Matrix::dotProduct(matrix); }
	double frobeniusNorm() const override;
	void transpose() override = 0;

};
