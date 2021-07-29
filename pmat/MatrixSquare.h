#pragma once

#include "Matrix.h"

class MatrixTriangular;

class MatrixSquare;

struct PLU
{
	MatrixSquare* matP{ nullptr };
	MatrixTriangular* matL{ nullptr };
	MatrixTriangular* matU{ nullptr };
	std::vector<std::pair<unsigned, unsigned>> swappedRows;
};


class MatrixSquare : public Matrix
{
public:

private:
	PLU _matsPLU;
	bool _changeSignForDet{ false };
	bool _calcLu{ false };
	bool _createLu{ false };
	void swapRowsBellow(MatrixSquare& matU, const unsigned int& idxPivot);
	void nullifyElementBellow(MatrixSquare& matU, const unsigned int& idxPivot) const;
	void decomposeToPlu();
	void findInverseByBackSubstitution(MatrixTriangular* matrix, MatrixTriangular* resp) const;

protected:
	void createLu();
	void destroyLu() const;

public:
	MatrixSquare() = default;
	explicit MatrixSquare(const unsigned int& size) : Matrix(size, size) {}
	MatrixSquare(const MatrixSquare& matrix) : Matrix(matrix) {}
	MatrixSquare(MatrixSquare&& matrix) noexcept : Matrix(std::move(matrix)) {}
	~MatrixSquare() override;
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
	inline const unsigned int& getSize() const { return this->getRowSize(); }
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	virtual double trace() const;
	virtual double determinant();
	virtual const PLU& getPLU();
	virtual bool isInvertible();
	MatrixTriangular extractLowerPart() const;
	MatrixTriangular extractUpperPart() const;
	MatrixSquare getInverse();



};

