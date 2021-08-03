#pragma once
#include "AbstractMatrixSymAntiSym.h"
class MatrixSkewSymmetric :
    public AbstractMatSymSkewSym
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
	MatrixSkewSymmetric operator+(const MatrixSkewSymmetric & matrix) const;
	MatrixSkewSymmetric operator-(const MatrixSkewSymmetric & matrix) const;
	MatrixSkewSymmetric operator*(const double& scalar) const;
	void transpose() override;


};

