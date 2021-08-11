#pragma once

#include "MatrixSquare.h"


class AbstractMatrixTriangular : public MatrixSquare
{
private:
	bool _isLower{ true };

protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override = 0;

	unsigned getVectorSize() const override { return (_rowSize * _rowSize + _rowSize) / 2; }

public:
	virtual bool isLower() const = 0;
	void reset(const unsigned& size) override = 0;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override = 0;
	bool operator==(const MatrixSquare& matrix) const { return MatrixSquare::operator==(matrix); }
	MatrixSquare asMatrixSquare() const;
	double dotProduct(const Matrix& matrix) const override = 0;
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const override = 0;
	void times(const Matrix& matrix, Matrix& resp) const override { MatrixSquare::times(matrix, resp); }
	void times(const Vector& vector, Vector& resp) const override = 0;
	void times(const double& scalar, MatrixSquare& resp) const override { MatrixSquare::times(scalar, resp); }
	void times(const double& scalar, Matrix& resp) const override { MatrixSquare::times(scalar, resp); }
	double frobeniusNorm() const override;
	void transpose() override
	{
		throw std::logic_error(messages::MATRIX_NOT_TRANSP);
	}
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
	void fillRandomly(const double& min, const double& max) override = 0;
	double determinant() override;
};


