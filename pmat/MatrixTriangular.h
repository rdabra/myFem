#pragma once

#include "MatrixSquare.h"


class MatrixTriangular : public MatrixSquare
{
private:
	bool _isLower{ true };

protected:
	unsigned int getVectorIndex(const unsigned int& i, const unsigned int& j) const override
	{
		return _isLower ? (i * (i + 1)) / 2 + j : (j * (j + 1)) / 2 + i;
	}

	unsigned int getVectorSize() const override { return (_rowSize * _rowSize + _rowSize) / 2; }

public:
	MatrixTriangular() = default;
	MatrixTriangular(const unsigned int& size, bool isLower);
	MatrixTriangular(const MatrixTriangular& matrix);
	MatrixTriangular(MatrixTriangular&& matrix) noexcept;
	~MatrixTriangular() override = default;
	const bool& isLower() const { return _isLower; }
	void resize(const unsigned int& size, bool isLower);
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const override;
	bool operator==(MatrixTriangular& matrix) const;
	bool operator==(MatrixSquare& matrix) const { return MatrixSquare::operator==(matrix); }
	MatrixTriangular& operator=(const MatrixTriangular& matrix);
	MatrixTriangular& operator=(MatrixTriangular&& matrix) noexcept;
	double dotProduct(const Matrix& matrix) const override;
	void plus(const MatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void addBy(const MatrixTriangular& matrix);
	void addBy(const Matrix& matrix) override { Matrix::addBy(matrix); }
	void minus(const MatrixTriangular& matrix, MatrixSquare& resp) const;
	MatrixSquare operator+(const MatrixTriangular& matrix) const;
	MatrixSquare operator-(const MatrixTriangular& matrix) const;
	virtual void subtractBy(const MatrixTriangular& matrix);
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const;
	void times(const Vector& vector, Vector& resp) const override;
	void times(const double& scalar, MatrixTriangular& resp) const;
	MatrixSquare operator*(const MatrixSquare& matrix) const override;
	MatrixTriangular operator*(const double& scalar) const;
	Vector operator*(const Vector& vector) const override;
	void multiplyBy(const double& scalar) override;
	double frobeniusNorm() const override;
	void transpose() override;
	void swapRows(const unsigned int& rowIndexA, const unsigned int& rowIndexB) override
	{
		throw std::logic_error(messages::ELEM_SWAPPED);
	}
	void swapRowElements(const unsigned int& rowIndexA, const unsigned int& rowIndexB, const unsigned int& startColumn,
		const unsigned int& endColumn) override;
	void swapColumns(const unsigned int& columnIndexA, const unsigned int& columnIndexB) override
	{
		throw std::logic_error(messages::ELEM_SWAPPED);
	}
	void swapColumnElements(const unsigned int& columnIndexA, const unsigned int& columnIndexB,
		const unsigned int& startRow, const unsigned int& endRow) override;
	void fillRandomly(const double& min, const double& max) override;
	double determinant() override;
};
