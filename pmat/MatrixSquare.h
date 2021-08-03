#pragma once

#include "Matrix.h"


class MatrixTriangular;

class MatrixSquare;

class MatrixSymmetric;

class MatrixSkewSymmetric;

struct D_PLU
{
	MatrixSquare* matP{ nullptr };
	MatrixTriangular* matL{ nullptr };
	MatrixTriangular* matU{ nullptr };
	std::vector<std::pair<unsigned, unsigned>> swappedRows;
};

struct D_SAS
{
	MatrixSymmetric* matS{ nullptr };
	MatrixSkewSymmetric* matAS{ nullptr };
};


class MatrixSquare : public Matrix
{
protected:
	D_PLU _matsPLU;
	D_SAS _matsSAS;
	bool _changeSignForDet{ false };
	bool _calcLu{ false };
	bool _calcStrictLu{ false };
	bool _calcSas{ false };
	bool _createLu{ false };
	bool _createSas{ false };
	void swapRowsBellow(MatrixSquare& matU, const unsigned& idxPivot);
	void nullifyElementBellow(MatrixSquare& matU, const unsigned& idxPivot) const;
	void findInverseByBackSubstitution(MatrixTriangular* matrix, MatrixTriangular* resp) const;
	void createLu();
	void destroyLu();
	void createSas();
	void destroySas();
	virtual void decomposeToPlu();
	virtual void decomposeToStrictLu();
	virtual void decomposeToSas();

public:
	MatrixSquare() = default;
	explicit MatrixSquare(const unsigned& size) : Matrix(size, size) { }
	MatrixSquare(const MatrixSquare& matrix) : Matrix(matrix) {}
	MatrixSquare(MatrixSquare&& matrix) noexcept : Matrix(std::move(matrix)) {}
	~MatrixSquare() override;
	void reset(const unsigned& size) { Matrix::reset(size,size); }
	MatrixSquare& operator=(const MatrixSquare& matrix);
	MatrixSquare& operator=(MatrixSquare&& matrix) noexcept;
	MatrixSquare operator+(const MatrixSquare& matrix) const;
	MatrixSquare operator-(const MatrixSquare& matrix) const;
	virtual void times(const MatrixSquare& matrix, MatrixSquare& resp) const { Matrix::times(matrix, resp); }
	void times(const Matrix& matrix, Matrix& resp) const override { Matrix::times(matrix, resp); }
	virtual void times(const double& scalar, MatrixSquare& resp) const { Matrix::times(scalar, resp); }
	void times(const double& scalar, Matrix& resp) const override { Matrix::times(scalar, resp); }
	virtual MatrixSquare operator*(const MatrixSquare& matrix) const;
	MatrixSquare operator*(const double& scalar) const;
	void times(const Vector& vector, Vector& resp) const override { Matrix::times(vector, resp); }
	Vector operator*(const Vector& vector) const override { return Matrix::operator*(vector); }
	const unsigned& getSize() const { return this->getRowSize(); }
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	virtual double trace() const;
	virtual double determinant();
	virtual const D_PLU& getPLU();
	virtual const D_PLU& getStrictLU();
	virtual const D_SAS& getSAS();
	virtual bool isStrictLUDecomposable();
	virtual bool isInvertible();
	virtual MatrixTriangular extractLowerPart() const;
	virtual MatrixTriangular extractUpperPart() const;
	virtual MatrixSquare getInverse();
	virtual bool isPositiveDefinite();
};
