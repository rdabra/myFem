#pragma once
#include "MatrixSquare.h"

class MatrixSymmetric :
    public MatrixSquare
{
private:
	std::vector<double> _matrix; // Changing visibility in order to prevent inheritance

protected:
	MatrixTriangular _matTri;

public:
	MatrixSymmetric() = default;
	explicit MatrixSymmetric(const unsigned int& size);
	MatrixSymmetric(const MatrixSymmetric& matrix);
	MatrixSymmetric(MatrixSymmetric&& matrix) noexcept;
	~MatrixSymmetric() override = default;
	const double& operator()(const unsigned int& rowIndex, const unsigned int& columnIndex) const override;
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	void resize(const unsigned int& size);
	bool operator==(MatrixSymmetric& matrix) const;
	MatrixSymmetric& operator=(const MatrixSymmetric& matrix);
	MatrixSymmetric& operator=(MatrixSymmetric&& matrix) noexcept;
	double dotProduct(const MatrixSymmetric& matrix) const;
	double dotProduct(const Matrix& matrix) const override { return Matrix::dotProduct(matrix); }
	void plus(const MatrixSymmetric& matrix, MatrixSymmetric& resp) const;



};

