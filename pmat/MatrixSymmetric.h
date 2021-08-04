#pragma once

#include "AbstractMatrixSymSkewSym.h"

/**
 * @TODO Em MatrixSymmetric implementar Cholesky
*/
class MatrixSymmetric :
	public AbstractMatSymSkewSym
{

public:
	MatrixSymmetric() = default;
	explicit MatrixSymmetric(const unsigned& size);
	MatrixSymmetric(const MatrixSymmetric& matrix);
	MatrixSymmetric(MatrixSymmetric&& matrix) noexcept;
	~MatrixSymmetric() override = default;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	MatrixSymmetric& operator=(const MatrixSymmetric& matrix);
	MatrixSymmetric& operator=(MatrixSymmetric&& matrix) noexcept;
	MatrixSymmetric operator+(const MatrixSymmetric& matrix) const;
	MatrixSquare operator+(const AbstractMatSymSkewSym& matrix) const { return MatrixSquare::operator+(matrix); }
	MatrixSymmetric operator-(const MatrixSymmetric& matrix) const;
	MatrixSquare operator-(const AbstractMatSymSkewSym& matrix) const { return MatrixSquare::operator-(matrix); }
	MatrixSquare operator*(const MatrixSymmetric& matrix) const { return AbstractMatSymSkewSym::operator*(matrix); }
	MatrixSymmetric operator*(const double& scalar) const;
	void transpose() override {}

};

