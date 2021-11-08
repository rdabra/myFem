#pragma once
#include "MatrixSquare.h"

/**
 * @todo Oitimizar multiplicacao por vetor 
*/
class MatrixDiagonal final :
	public MatrixSquare
{
protected:
	unsigned getVectorIndex(const unsigned& i, const unsigned& j) const override { return i; }
	unsigned getVectorSize() const override { return _rowSize; }
	void decomposeToPlu() override;
	void decomposeToStrictLu() override;
	void decomposeToSas() override;

public:
	MatrixDiagonal() = default;
	explicit MatrixDiagonal(const unsigned& size);
	MatrixDiagonal(const MatrixDiagonal& matrix);
	MatrixDiagonal(MatrixDiagonal&& matrix) noexcept : MatrixSquare(std::move(matrix)) {}
	~MatrixDiagonal() override = default;
	MatrixDiagonal& operator=(const MatrixDiagonal& matrix);
	MatrixDiagonal& operator=(MatrixDiagonal&& matrix) noexcept;
	bool operator==(MatrixDiagonal& matrix) const;
	bool operator==(const MatrixSquare& matrix) const { return MatrixSquare::operator==(matrix); }
	MatrixSquare asMatrixSquare() const;
	MatrixDiagonal operator+(const MatrixDiagonal& matrix) const;
	MatrixDiagonal operator-(const MatrixDiagonal& matrix) const;
	virtual void subtractBy(const MatrixDiagonal& matrix);
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	double dotProduct(const Matrix& matrix) const override;
	void plus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	virtual void addBy(const MatrixDiagonal& matrix);
	void minus(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	void times(const MatrixDiagonal& matrix, MatrixDiagonal& resp) const;
	void times(const MatrixSquare& matrix, MatrixSquare& resp) const override { MatrixSquare::times(matrix, resp); }
	void times(const Vector& vector, Vector& resp) const override;
	void times(const double& scalar, MatrixDiagonal& resp) const;
	void times(const double& scalar, Matrix& resp) const  override { MatrixSquare::times(scalar, resp); }
	void multiplyBy(const double& scalar) override;
	double getFrobeniusNorm() const override;
	void transpose() override {}
	void fillRandomly(const double& min, const double& max) override;
	double getDeterminant() override;
	bool isStrictLUDecomposable() override;
	bool isInvertible() override;
	MatrixLowerTriangular extractLowerPart() const override;
	MatrixUpperTriangular extractUpperPart() const override;
	MatrixSquare getInverse() override;
	bool isPositiveDefinite() override;
	void copyElementsFrom(const MatrixDiagonal& matrix);
};
