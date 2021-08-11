#pragma once

#include "AbstractMatrixSymmetry.h"

/**
 * @TODO Em MatrixSymmetric implementar Cholesky
*/
class MatrixSymmetric :
	public AbstractMatrixSymmetry
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
	MatrixSquare operator+(const AbstractMatrixSymmetry& matrix) const { return MatrixSquare::operator+(matrix); }
	MatrixSymmetric operator-(const MatrixSymmetric& matrix) const;
	MatrixSquare operator-(const AbstractMatrixSymmetry& matrix) const { return MatrixSquare::operator-(matrix); }
	MatrixSquare operator*(const MatrixSymmetric& matrix) const { return AbstractMatrixSymmetry::operator*(matrix); }
	MatrixSymmetric operator*(const double& scalar) const;
	void transpose() override {}

};

