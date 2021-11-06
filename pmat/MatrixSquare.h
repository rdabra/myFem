#pragma once

#include "Matrix.h"


class AbstractMatrixTriangular;

class MatrixLowerTriangular;

class MatrixUpperTriangular;

class MatrixSquare;

class MatrixSymmetric;

class MatrixSkewSymmetric;

enum class SubMatrixPos {lower,upper};

struct D_PLU
{
	MatrixSquare* matP{ nullptr };
	MatrixLowerTriangular* matL{ nullptr };
	MatrixUpperTriangular* matU{ nullptr };
	std::vector<std::pair<unsigned, unsigned>> swappedRows;
};

struct D_SAS
{
	MatrixSymmetric* matS{ nullptr };
	MatrixSkewSymmetric* matAS{ nullptr };
};

struct D_PQR
{
	MatrixSquare* matP{ nullptr };
	MatrixSquare* matQ{ nullptr };
	MatrixUpperTriangular* matR{ nullptr };
	std::vector<std::pair<unsigned, unsigned>> swappedColumns;
	unsigned rank {0};
};


/**
 * @todo Implementar decomposição QR e obter o rank
 * @todo Implementar Singular Value Decompostion
 * @todo Implementer Multiplciacao por submatrix e documentar 
*/
class MatrixSquare : public Matrix
{
protected:
	D_PLU _matsPLU;
	D_SAS _matsSAS;
	D_PQR  _matsQR;
	bool _changeSignForDet{ false };
	bool _calcLu{ false };
	bool _calcStrictLu{ false };
	bool _calcSas{ false };
	bool _calcQR {false};
	bool _createLu{ false };
	bool _createSas{ false };
	bool _createQR{ false };
	void swapRowsBellow(MatrixSquare& matU, const unsigned& idxPivot);
	void swapPivotColumn(MatrixSquare& partialR, const unsigned& idxPivot);
	void nullifyElementBellow(MatrixSquare& matU, const unsigned& idxPivot) const;
	void findInverseByBackSubstitution(const AbstractMatrixTriangular* matrix, AbstractMatrixTriangular* resp) const;
	Vector findSolutionByBackSubstitution(const AbstractMatrixTriangular& matrix, const Vector& rhs) const;
	MatrixSquare calculateHouseholderSubMatrix(const MatrixSquare& partialR, const unsigned idxPivot) const;
	MatrixSquare calculateInverseByPlu();
	MatrixSquare calculateInverseByPQR();
	void createLu();
	void destroyLu();
	void createSas();
	void destroySas();
	void createQr();
	void destroyQr();
	virtual void decomposeToPlu();
	virtual void decomposeToStrictLu();
	virtual void decomposeToSas();
	virtual void decomposeToQr();

public:
	MatrixSquare() = default;
	explicit MatrixSquare(const unsigned& size) : Matrix(size, size) { }
	MatrixSquare(const MatrixSquare& matrix) : Matrix(matrix) {}
	MatrixSquare(MatrixSquare&& matrix) noexcept : Matrix(std::move(matrix)) {}
	~MatrixSquare() override;
	virtual void reset(const unsigned& size) { Matrix::reset(size,size); }
	virtual MatrixSquare toMatrixSquare() const;
	MatrixSquare& operator=(const MatrixSquare& matrix);
	MatrixSquare& operator=(MatrixSquare&& matrix) noexcept;
	MatrixSquare operator+(const MatrixSquare& matrix) const;
	MatrixSquare operator-(const MatrixSquare& matrix) const;
	virtual void times(const MatrixSquare& matrix, MatrixSquare& resp) const { Matrix::times(matrix, resp); }
	void times(const double& scalar, Matrix& resp) const override { Matrix::times(scalar, resp); }
	virtual MatrixSquare operator*(const MatrixSquare& matrix) const;
	virtual MatrixSquare multiplyByBiggerMatrix(const MatrixSquare& matrix, SubMatrixPos pos);
	MatrixSquare operator*(const double& scalar) const;
	void times(const Vector& vector, Vector& resp) const override { Matrix::times(vector, resp); }
	Vector operator*(const Vector& vector) const override { return Matrix::operator*(vector); }
	const unsigned& getSize() const { return Matrix::getRowSize(); }
	void setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex) override;
	virtual double trace() const;
	virtual double determinant();
	virtual const D_PLU& getPLU();
	virtual const D_PLU& getStrictLU();
	virtual const D_SAS& getSAS();
	virtual const D_PQR& getPQR();
	virtual bool isStrictLUDecomposable();
	virtual bool isInvertible();
	virtual MatrixLowerTriangular extractLowerPart() const;
	virtual MatrixUpperTriangular extractUpperPart() const;
	virtual MatrixSquare getInverse();
	virtual Vector linearSolve(const Vector& rhs);
	virtual bool isPositiveDefinite();
	virtual bool isOrthogonal();
	unsigned rank();
};
