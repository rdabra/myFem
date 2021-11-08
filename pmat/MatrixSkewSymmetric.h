#pragma once
#include "AbstractMatrixSymmetry.h"

/**
 * @todo Implementar construtor recebendo MatrixLowerTriangular
 */
class MatrixSkewSymmetric :
    public AbstractMatrixSymmetry
{

public:
	MatrixSkewSymmetric() = default;
	explicit MatrixSkewSymmetric(const unsigned& size);
	MatrixSkewSymmetric(const MatrixSkewSymmetric & matrix);
	MatrixSkewSymmetric(MatrixSkewSymmetric && matrix) noexcept;
	~MatrixSkewSymmetric() override = default;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	MatrixSkewSymmetric& operator=(const MatrixSkewSymmetric & matrix);
	MatrixSkewSymmetric& operator=(MatrixSkewSymmetric && matrix) noexcept;
	MatrixSkewSymmetric operator+(const MatrixSkewSymmetric& matrix) const;
	MatrixSquare operator+(const AbstractMatrixSymmetry& matrix) const { return MatrixSquare::operator+(matrix); }
	MatrixSkewSymmetric operator-(const MatrixSkewSymmetric& matrix) const;
	MatrixSquare operator-(const AbstractMatrixSymmetry& matrix) const { return MatrixSquare::operator-(matrix); }
	MatrixSquare operator*(const MatrixSkewSymmetric& matrix) const { return AbstractMatrixSymmetry::operator*(matrix); }
	MatrixSkewSymmetric operator*(const double& scalar) const;
	void transpose() override;

};

