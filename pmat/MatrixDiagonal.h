#pragma once
#include "MatrixSquare.h"

/**
 * @TODO Implementar um pai para MatrixDiagonal que é MatrixSymmetric
 * @TODO Em MatrixSymmetric implementar Cholesky
*/
class MatrixDiagonal final :
	public MatrixSquare
{
protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override { return i; }
	unsigned getVectorSize() const override { return _rowSize; }

public:
	MatrixDiagonal() = default;
	explicit MatrixDiagonal(const unsigned& size);
	MatrixDiagonal(const MatrixDiagonal& matrix);
	MatrixDiagonal(MatrixDiagonal&& matrix) noexcept : MatrixSquare(std::move(matrix)) {}
	~MatrixDiagonal() override = default;
	MatrixDiagonal& operator=(const MatrixDiagonal& matrix);
	MatrixDiagonal& operator=(MatrixDiagonal&& matrix) noexcept;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	const double& operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	double dotProduct(const Matrix& matrix) const override;
	void plus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	virtual void addBy(const MatrixDiagonal& matrix);
	void minus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	virtual void subtractBy(const MatrixDiagonal& matrix);
	void times(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	void times(const Vector& vector, Vector& resp) const override;
	void times(const double& scalar, MatrixDiagonal& resp) const;
	void multiplyBy(const double& scalar) override;
	double frobeniusNorm() const override;
	void transpose() override {}
	void fillRandomly(const double& min, const double& max) override;
	double determinant() override;
};
