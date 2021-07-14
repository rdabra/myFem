#pragma once

#include "Matrix.h"

class MatrixSquare : public Matrix
{
private:
	MatrixSquare* _matP{ nullptr };
	MatrixSquare* _matL{ nullptr };
	MatrixSquare* _matU{ nullptr };
	unsigned int _numExchangesP{ 0 };
	bool _calcLu{ false };
	bool _createLu{ false };
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
	inline const unsigned int& getSize() const { return this->getRowSize(); }
	void setValue(const double& value, const unsigned int& rowIndex, const unsigned int& columnIndex) override;
	virtual double trace() const;
	virtual void decomposeToPlu();
	virtual double determinant() ;
};
