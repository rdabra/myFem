#pragma once
#include "AbstractMatrixTriangular.h"
#include "MatrixLowerTriangular.h"

class MatrixUpperTriangular :
    public AbstractMatrixTriangular
{
protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override
	{
		return (j * (j + 1)) / 2 + i;
	}


public:
	MatrixUpperTriangular() = default;
	explicit MatrixUpperTriangular(const unsigned& size);
	MatrixUpperTriangular(const MatrixUpperTriangular & matrix);
	MatrixUpperTriangular(MatrixUpperTriangular && matrix) noexcept;
	~MatrixUpperTriangular() override = default;
	bool isLower() const override { return false; }
	void reset(const unsigned& size) override;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	bool operator==(const MatrixUpperTriangular & matrix) const;
	MatrixUpperTriangular& operator=(const MatrixUpperTriangular & matrix);
	MatrixUpperTriangular& operator=(MatrixUpperTriangular && matrix) noexcept;
	double dotProduct(const Matrix & matrix) const override;
	void plus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void addBy(const MatrixUpperTriangular & matrix);
	void minus(const AbstractMatrixTriangular& matrix, MatrixSquare& resp) const;
	virtual void subtractBy(const MatrixUpperTriangular & matrix);
	void times(const MatrixSquare & matrix, MatrixSquare & resp) const override;
	void times(const Vector & vector, Vector & resp) const override;
	virtual void times(const double& scalar, MatrixUpperTriangular & resp) const;
	void multiplyBy(const double& scalar) override;
	MatrixLowerTriangular getTranspose() const;
	void swapRowElements(const unsigned& rowIndexA, const unsigned& rowIndexB, const unsigned& startColumn,
		const unsigned& endColumn) override;
	void swapColumnElements(const unsigned& columnIndexA, const unsigned& columnIndexB,
		const unsigned& startRow, const unsigned& endRow) override;
	void fillRandomly(const double& min, const double& max) override;

};

