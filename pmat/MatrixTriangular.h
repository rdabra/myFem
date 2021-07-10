#pragma once

#include "MatrixSquare.h"

class MatrixTriangular : public MatrixSquare
{
private:
	bool _isLower{ true };

protected:
	inline virtual unsigned int getVectorIndex(const unsigned int& i, const unsigned int& j) const
	{
		return _isLower ? (i * (i + 1)) / 2 + j : (j * (j + 1)) / 2 + i;
	};
	inline virtual unsigned int getVectorSize()  const { return (_rowSize * _rowSize + _rowSize) / 2; };

public:
	MatrixTriangular(const unsigned int& size, bool isLower);
	MatrixTriangular(const MatrixTriangular& matrix);
	MatrixTriangular(MatrixTriangular&& matrix) noexcept;
	virtual ~MatrixTriangular() {};
	inline const bool& isLower() const { return _isLower; };
	virtual void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex);
	virtual const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const;
	MatrixTriangular& operator=(const MatrixTriangular& matrix);
	MatrixTriangular& operator=(MatrixTriangular&& matrix) noexcept;
	double dotProduct(const MatrixSquare& matrix) const;
	void plus(const MatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void addBy(const MatrixTriangular& matrix);
	void minus(const MatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void subtractBy(const MatrixTriangular& matrix);
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const;
	void times(const Vector& vector, Vector& resp) const;
	void times(const double& scalar, MatrixTriangular& resp) const;
	virtual void multiplyBy(const double& scalar);
	virtual double frobeniusNorm() const;
	virtual void transpose();
	virtual void swapRows(const unsigned int& rowIndexA, const unsigned int& rowIndexB) { throw std::logic_error(messages::ELEM_SWAPPED); };
	virtual void swapRowElements(const unsigned int& rowIndexA, const unsigned int& rowIndexB, const unsigned int& startColumn, const unsigned int& endColumn);
	virtual void swapColumns(const unsigned int& columnIndexA, const unsigned int& columnIndexB) { throw std::logic_error(messages::ELEM_SWAPPED); };
	virtual void swapColumnElements(const unsigned int& columnIndexA, const unsigned int& columnIndexB, const unsigned int& startRow, const unsigned int& endRow);
	virtual void fillRandomly(const double& min, const double& max);
	virtual double determinant() const;
};
