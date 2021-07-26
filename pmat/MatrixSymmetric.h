#pragma once
#include "MatrixSquare.h"

class MatrixSymmetric :
    public MatrixSquare
{
private:
	std::vector<double> _matrix; // In order to prevent from being inherited

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



};

