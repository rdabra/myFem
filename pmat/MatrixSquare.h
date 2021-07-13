#pragma once

#include<cmath>
#include "Matrix.h"

class MatrixSquare : public Matrix
{
private:
	MatrixSquare* _matP{ nullptr };
	MatrixSquare* _matL{ nullptr };
	MatrixSquare* _matU{ nullptr };
	unsigned int _numExchangesP{ 0 };
	bool _calcLU{ false };
	bool _createLU{ false };
	void nullifyElementBellow(const unsigned int& idxPivot);

protected:
	MatrixSquare() {};
	void createLU();
	void destroyLU();

public:
	MatrixSquare(const unsigned int& size) : Matrix(size, size) {};
	MatrixSquare(const MatrixSquare& matrix) : Matrix(matrix) {};
	MatrixSquare(MatrixSquare&& matrix) noexcept : Matrix(matrix) {};
	virtual ~MatrixSquare();
	inline const unsigned int& getSize() const { return this->getRowSize(); };
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual double trace() const;
	virtual void decomposeToPLU();
	virtual double determinant();
};
