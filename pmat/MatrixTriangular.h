#pragma once

#include "MatrixSquare.h"


class MatrixTriangular : public MatrixSquare
{
private:
	bool _isLower{ true };

protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override
	{
		return _isLower ? (i * (i + 1)) / 2 + j : (j * (j + 1)) / 2 + i;
	}

	unsigned getVectorSize() const override { return (_rowSize * _rowSize + _rowSize) / 2; }

public:
	MatrixTriangular() = default;
	MatrixTriangular(const unsigned& size, bool isLower);
	MatrixTriangular(const MatrixTriangular& matrix);
	MatrixTriangular(MatrixTriangular&& matrix) noexcept;
	~MatrixTriangular() override = default;
	const bool& isLower() const { return _isLower; }
	void reset(const unsigned& size, bool isLower);
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	bool operator==(MatrixTriangular& matrix) const;
	bool operator==(MatrixSquare& matrix) const { return MatrixSquare::operator==(matrix); }
	MatrixTriangular& operator=(const MatrixTriangular& matrix);
	MatrixTriangular& operator=(MatrixTriangular&& matrix) noexcept;
	MatrixSquare asMatrixSquare() const;
	double dotProduct(const Matrix& matrix) const override;
	void plus(const MatrixTriangular& matrix, MatrixSquare& resp) const; 
	virtual void addBy(const MatrixTriangular& matrix);
	void minus(const MatrixTriangular& matrix, MatrixSquare& resp) const;
	MatrixSquare operator+(const MatrixTriangular& matrix) const;
	MatrixSquare operator-(const MatrixTriangular& matrix) const;
	virtual void subtractBy(const MatrixTriangular& matrix);
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const override;
	void times(const Matrix& matrix, Matrix& resp) const override { MatrixSquare::times(matrix, resp); }
	void times(const Vector& vector, Vector& resp) const override;
	virtual void times(const double& scalar, MatrixTriangular& resp) const;
	void times(const double& scalar, MatrixSquare& resp) const override { MatrixSquare::times(scalar, resp); }
	void times(const double& scalar, Matrix& resp) const override { MatrixSquare::times(scalar, resp); }
	MatrixSquare operator*(const MatrixSquare& matrix) const override;
	MatrixTriangular operator*(const double& scalar) const;
	Vector operator*(const Vector& vector) const override;
	void multiplyBy(const double& scalar) override;
	double frobeniusNorm() const override;
	void transpose() override;
	void swapRows(const unsigned& rowIndexA, const unsigned& rowIndexB) override
	{
		throw std::logic_error(messages::ELEM_SWAPPED);
	}
	MatrixSquare getSwappedByRows(const unsigned& rowIndexA, const unsigned& rowIndexB) const;
	void swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB, const unsigned& startColumn,
		const unsigned& endColumn) override;
	void swapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB) override
	{
		throw std::logic_error(messages::ELEM_SWAPPED);
	}
	MatrixSquare getSwappedByColumns(const unsigned& columnIndexA, const unsigned& columnIndexB) const;
	void swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
		const unsigned& startRow, const unsigned& endRow) override;
	void fillRandomly(const double& min, const double& max) override;
	double determinant() override;
};
