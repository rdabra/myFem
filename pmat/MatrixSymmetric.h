#pragma once
#include "MatrixSquare.h"

class MatrixSymmetric :
	public MatrixSquare
{
private:
	std::vector<double> _matrix; // Changing visibility in order to prevent inheritance
	bool _antiSymmetric{ false };

protected:
	MatrixTriangular _matTri;

public:
	MatrixSymmetric() = default;
	MatrixSymmetric(const unsigned& size, bool antiSymmetric);
	MatrixSymmetric(const MatrixSymmetric& matrix);
	MatrixSymmetric(MatrixSymmetric&& matrix) noexcept;
	~MatrixSymmetric() override = default;
	double operator()(const unsigned& rowIndex, const unsigned& columnIndex) const override;
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	void reset(const unsigned& size, bool antiSymmetric);
	const bool& isAntiSymmetric() const { return _antiSymmetric; }
	bool operator==(MatrixSymmetric& matrix) const;
	MatrixSymmetric& operator=(const MatrixSymmetric& matrix);
	MatrixSymmetric& operator=(MatrixSymmetric&& matrix) noexcept;
	double dotProduct(const MatrixSymmetric& matrix) const;
	double dotProduct(const Matrix& matrix) const override { return Matrix::dotProduct(matrix); }
	void plus(const MatrixSymmetric& matrix, MatrixSymmetric& resp) const;
	virtual void addBy(const MatrixSymmetric& matrix);
	void addBy(const Matrix& matrix) override { Matrix::addBy(matrix); }
	void minus(const MatrixSymmetric& matrix, MatrixSymmetric& resp) const;
	MatrixSymmetric operator+(const MatrixSymmetric& matrix) const;
	MatrixSymmetric operator-(const MatrixSymmetric& matrix) const;
	virtual void subtractBy(const MatrixSymmetric& matrix);
	void subtractBy(const Matrix& matrix) override { Matrix::subtractBy(matrix); }
	void multiplyBy(const double& scalar) override;
	virtual MatrixSquare operator*(const MatrixSymmetric& matrix) const { return MatrixSquare::operator*(matrix); }
	MatrixSymmetric operator*(const double& scalar) const;
	double frobeniusNorm() const override;
	void transpose() override {}

};

