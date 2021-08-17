#pragma once

#include "AbstractMatrixSymmetry.h"
#include "MatrixLowerTriangular.h"

class MatrixSymmetric :
	public AbstractMatrixSymmetry
{

private:
	MatrixLowerTriangular* _choleskyFactor{ nullptr };
	bool _createL{ false };
	bool _calcL{ false };
	void createL();
	void destroyL();
	void decomposeToCholesky();


public:
	MatrixSymmetric() = default;
	explicit MatrixSymmetric(const unsigned& size);
	MatrixSymmetric(const MatrixSymmetric& matrix);
	explicit MatrixSymmetric(const MatrixLowerTriangular& matrix);
	MatrixSymmetric(MatrixSymmetric&& matrix) noexcept;
	explicit MatrixSymmetric(MatrixLowerTriangular&& matrix) noexcept;
	~MatrixSymmetric() override;
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
	MatrixLowerTriangular& getCholeskyFactor();
	double determinant() override;
	MatrixSymmetric getInverseAsSymmetric();
	MatrixSquare getInverse() override;
	bool isPositiveDefinite() override;

};

