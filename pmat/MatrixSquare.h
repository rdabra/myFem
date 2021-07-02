#pragma once

#include "Matrix.h"


class MatrixSquare : public Matrix
{
private:
	Matrix* _matP = NULL;
	Matrix* _matL = NULL;
	Matrix* _matU = NULL;
	bool _calcLU{ false };
	bool _createLU{ false };
	void fillLU();

protected:
	MatrixSquare() {};
	void createLU();

public:
	MatrixSquare(const unsigned int& size) : Matrix(size, size) {};
	MatrixSquare(const MatrixSquare& matrix) : Matrix(matrix) {};
	MatrixSquare(MatrixSquare&& matrix) noexcept : Matrix(matrix) {} ;
	virtual ~MatrixSquare();
	inline const unsigned int& getSize() const { return this->getRowSize(); };
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual double trace() const;
	virtual double determinant() const;
};

