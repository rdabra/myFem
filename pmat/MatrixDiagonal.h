#pragma once
#include "MatrixSquare.h"

class MatrixDiagonal final :
	public MatrixSquare
{
protected:
	unsigned int getVectorIndex(const unsigned int& i, const unsigned int& j) const override { return i; }
	unsigned int getVectorSize() const override { return _rowSize; }

public:
	MatrixDiagonal() = default;
	explicit MatrixDiagonal(const unsigned int& size);
	MatrixDiagonal(const MatrixDiagonal& matrix);
	MatrixDiagonal(MatrixDiagonal&& matrix) noexcept : MatrixSquare(std::move(matrix)) {}
	~MatrixDiagonal() override = default;
	MatrixDiagonal& operator=(const MatrixDiagonal& matrix);
	MatrixDiagonal& operator=(MatrixDiagonal&& matrix) noexcept;
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const override;
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
