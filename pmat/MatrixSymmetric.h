#pragma once
#include "AbstractMatrixSymAntiSym.h"

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
	MatrixSymmetric operator-(const MatrixSymmetric& matrix) const;
	MatrixSymmetric operator*(const double& scalar) const;
	void transpose() override {};

};

