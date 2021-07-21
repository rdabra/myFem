#pragma once

#include "Matrix.h"

class MatrixSquare;

struct PLU
{
	MatrixSquare* matP{ nullptr };
	MatrixSquare* matL{ nullptr };
	MatrixSquare* matU{ nullptr };
};


class MatrixSquare : public Matrix
{
public:

private:
	PLU _matsPLU;
	bool _changeSignForDet{ false };
	bool _calcLu{ false };
	bool _createLu{ false };
	void swapRowsBellow(const unsigned int& idxPivot);
	void nullifyElementBellow(const unsigned int& idxPivot) const;

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
	virtual MatrixSquare operator*(const MatrixSquare& matrix) const;
	MatrixSquare operator*(const double& scalar) const;
	Vector operator*(const Vector& vector) const override { return Matrix::operator*(vector); }
	inline const unsigned int& getSize() const { return this->getRowSize(); }
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	virtual double trace() const;
	virtual double determinant();
	virtual const PLU& getPLU();
};

