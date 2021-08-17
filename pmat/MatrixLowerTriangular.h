#pragma once
#include "AbstractMatrixTriangular.h"
#include "MatrixUpperTriangular.h"


class MatrixLowerTriangular :
	public AbstractMatrixTriangular
{

protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override
	{
		return (i * (i + 1)) / 2 + j;
	}

public:
	MatrixLowerTriangular() = default;
	explicit MatrixLowerTriangular(const unsigned& size);
	MatrixLowerTriangular(const MatrixLowerTriangular& matrix);
	MatrixLowerTriangular(MatrixLowerTriangular&& matrix) noexcept;
	~MatrixLowerTriangular() override = default;
	bool isLower() const override { return true; }
	void reset(const unsigned& size) override;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	bool operator==(const MatrixLowerTriangular& matrix) const;
	bool operator==(const MatrixSquare& matrix) const { return MatrixSquare::operator==(matrix); }
	MatrixLowerTriangular& operator=(const MatrixLowerTriangular& matrix);
	MatrixLowerTriangular& operator=(MatrixLowerTriangular&& matrix) noexcept;
	double dotProduct(const Matrix& matrix) const override;
	void plus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void addBy(const MatrixLowerTriangular& matrix);
	void minus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void subtractBy(const MatrixLowerTriangular& matrix);
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const override;
	void times(const Vector& vector, Vector& resp) const override;
	virtual void times(const double& scalar, MatrixLowerTriangular& resp) const;
	void multiplyBy(const double& scalar) override;
	MatrixLowerTriangular operator*(const double& scalar) const;
	Vector operator*(const Vector& vector) const override { return MatrixSquare::operator*(vector); }
	MatrixSquare operator*(const MatrixSquare& matrix) const override { return MatrixSquare::operator*(matrix); }
	MatrixUpperTriangular getTranspose() const;
	void partialSwapRows(const unsigned& rowIndexA, const unsigned& rowIndexB, const unsigned& startColumn,
		const unsigned& endColumn) override;
	void partialSwapColumns(const unsigned& columnIndexA, const unsigned& columnIndexB,
		const unsigned& startRow, const unsigned& endRow) override;
	void fillRandomly(const double& min, const double& max) override;
	MatrixSquare getInverse() override;
	virtual MatrixLowerTriangular getInverseAsLowerTriangular();

};

