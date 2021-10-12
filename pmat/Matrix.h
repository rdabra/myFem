#pragma once
#include <random>
#include <vector>
#include<algorithm>
#include "AbstractArray.h"
#include "Vector.h"

class Matrix : public AbstractArray
{
protected:
	bool _isTransposed{false};
	std::vector<double> _matrix;
	unsigned _rowSize{0}, _columnSize{0};

	virtual unsigned getVectorIndex(const unsigned& i, const unsigned& j) const
	{
		return _isTransposed ? i + j * _rowSize : j + i * _columnSize;
	}

	virtual unsigned getVectorSize() const { return _rowSize * _columnSize; }
	void validateIndex(const unsigned& rowIndex, const unsigned& columnIndex) const;
	void validateOperands(const Matrix& matrix) const;
	void validateResponse(Matrix& resp) const;
	void validateOperandMult(const Matrix& matrix) const;
	void validateResponseMult(const Matrix& matrix, const Matrix& resp) const;
	void validateVectorMult(const Vector& vector) const;
	void validateVectorRespMult(Vector& resp) const;

public:
	Matrix() = default;
	Matrix(const unsigned& rowSize, const unsigned& columnSize);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;
	virtual ~Matrix() = default;
	unsigned getArrayDimension() const override { return 2; }
	unsigned getNumberOfElements() const override { return _rowSize * _columnSize; }
	void reset(const unsigned& rowSize, const unsigned& columnSize);
	virtual double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const;
	virtual void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex);
	const unsigned& getRowSize(void) const { return _rowSize; }
	const unsigned& getColumnSize(void) const { return _columnSize; }
	Matrix& operator=(const Matrix& matrix);
	Matrix& operator=(Matrix&& matrix) noexcept;
	virtual bool operator==(const Matrix& matrix) const;
	virtual double dotProduct(const Matrix& matrix) const;
	void plus(const Matrix& matrix, Matrix& resp) const;
	Matrix operator+(const Matrix& matrix) const;
	void addBy(const Matrix& matrix);
	void minus(const Matrix& matrix, Matrix& resp) const;
	Matrix operator-(const Matrix& matrix) const;
	void subtractBy(const Matrix& matrix);
	void times(const Matrix& matrix, Matrix& resp) const;
	virtual Matrix operator*(const Matrix& matrix) const;
	virtual void times(const Vector& vector, Vector& resp) const;
	virtual Vector operator*(const Vector& vector) const;
	virtual void times(const double& scalar, Matrix& resp) const;
	Matrix operator*(const double& scalar) const;
	virtual void multiplyBy(const double& scalar);
	virtual void multiplyRowBy(const unsigned& rowIndex, const double& scalar);
	virtual void multiplyColumnBy(const unsigned& columnIndex, const double& scalar);
	virtual void partialSwapRows(const unsigned& rowIndexA, const unsigned& rowIndexB,
	                             const unsigned& startColumn, const unsigned& endColumn);
	virtual void swapRows(const unsigned& rowIndexA, const unsigned& rowIndexB);
	virtual void partialSwapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB,
	                                const unsigned& startRow, const unsigned& endRow);
	virtual void swapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB);
	virtual void transpose();
	virtual double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	Vector getRow(const unsigned& index) const;
	Vector getColumn(const unsigned& index) const;
	void copyElementsFrom(const Matrix& matrix);
};
