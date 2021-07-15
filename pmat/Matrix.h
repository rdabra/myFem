#pragma once
#include <random>
#include <vector>
#include "Vector.h"

class Matrix
{
protected:
	bool _isTransposed{false};
	std::vector<double> _matrix;
	unsigned int _rowSize{0}, _columnSize{0};

	virtual unsigned int getVectorIndex(const unsigned int& i, const unsigned int& j) const
	{
		return _isTransposed ? i + j * _rowSize : j + i * _columnSize;
	}

	virtual unsigned int getVectorSize() const { return _rowSize * _columnSize; }
	void validateIndex(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	void validateOperands(const Matrix& matrix) const;
	void validateResponse(Matrix& resp) const;
	void validateOperandMult(const Matrix& matrix) const;
	void validateResponseMult(const Matrix& matrix, const Matrix& resp) const;
	void validateVectorMult(const Vector& vector) const;
	void validateVectorRespMult(Vector& resp) const;

public:
	Matrix() = default;
	Matrix(const unsigned int& rowSize, const unsigned int& columnSize);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;
	virtual ~Matrix() = default;
	virtual const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual const unsigned int& getRowSize(void) const { return _rowSize; }
	virtual const unsigned int& getColumnSize(void) const { return _columnSize; }
	Matrix& operator=(const Matrix& matrix);
	Matrix& operator=(Matrix&& matrix) noexcept;
	virtual bool operator==(const Matrix& matrix) const;
	virtual double dotProduct(const Matrix& matrix) const;
	void plus(const Matrix& matrix, Matrix& resp) const;
	Matrix operator+(const Matrix& matrix) const;
	virtual void addBy(const Matrix& matrix);
	void minus(const Matrix& matrix, Matrix& resp) const;
	Matrix operator-(const Matrix& matrix) const;
	virtual void subtractBy(const Matrix& matrix);
	void times(const Matrix& matrix, Matrix& resp) const;
	Matrix operator*(const Matrix& matrix) const;
	virtual void times(const Vector& vector, Vector& resp) const;
	Vector operator*(const Vector& vector) const;
	void times(const double& scalar, Matrix& resp) const;
	Matrix operator*(const double& scalar) const;
	virtual void multiplyBy(const double& scalar);
	virtual void multiplyRowBy(const unsigned int& rowIndex, const double& scalar);
	virtual void multiplyColumnBy(const unsigned int& columnIndex, const double& scalar);
	virtual void swapRowElements(const unsigned int& rowIndexA, const unsigned int& rowIndexB,
	                             const unsigned int& startColumn, const unsigned int& endColumn);
	virtual void swapRows(const unsigned int& rowIndexA, const unsigned int& rowIndexB);
	virtual void swapColumnElements(const unsigned int& columnIndexA, const unsigned int& columnIndexB,
	                                const unsigned int& startRow, const unsigned int& endRow);
	virtual void swapColumns(const unsigned int& columnIndexA, const unsigned int& columnIndexB);
	virtual void transpose();
	virtual double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	virtual void copyFrom(const Matrix& matrix) { (*this) = matrix; }
};
