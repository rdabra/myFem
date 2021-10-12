#include "pch.h"
#include "MatrixSymmetric.h"


void MatrixSymmetric::createL()
{
	if (!_createL) {
		_choleskyFactor = new MatrixLowerTriangular(this->getSize());
		_createL = true;
		_calcL = false;
	}
}

void MatrixSymmetric::destroyL()
{
	if (_createL) {
		delete _choleskyFactor;
		_createL = false;
		_calcL = false;
	}
}

/**
 * @brief Performs the Cholesky decomposition of this matrix
*/
void MatrixSymmetric::decomposeToCholesky()
{
	if (!_calcL) {
		this->createL();
		for (unsigned i = 0; i < this->getSize(); ++i) {
			double diag = (*this)(i, i);
			for (unsigned k = 0; k < i; ++k)
				diag -= (*_choleskyFactor)(i, k) * (*_choleskyFactor)(i, k);
			if (putils::isZero(diag) || diag < putils::ZERO) {
				this->destroyL();
				throw std::logic_error(messages::MATRIX_NOT_L);
			}
			_choleskyFactor->setValue(std::sqrt(diag), i, i);
			for (unsigned j = i + 1; j < this->getSize(); ++j) {
				double aux = (*this)(i, j);
				for (unsigned k = 0; k < i; ++k)
					aux -= (*_choleskyFactor)(i, k) * (*_choleskyFactor)(j, k);
				_choleskyFactor->setValue(aux / (*_choleskyFactor)(i, i), j, i);
			}
		}


		_calcL = true;
	}
}

MatrixSymmetric::MatrixSymmetric(const unsigned& size)
{
	_rowSize = size;
	_columnSize = size;
	_matTri.reset(size);
}

MatrixSymmetric::MatrixSymmetric(const MatrixSymmetric& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = matrix._matTri;
}

MatrixSymmetric::MatrixSymmetric(const MatrixLowerTriangular& matrix)
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = matrix;
}

MatrixSymmetric::MatrixSymmetric(MatrixSymmetric&& matrix) noexcept
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = std::move(matrix._matTri);
	matrix.~MatrixSymmetric();
}

MatrixSymmetric::MatrixSymmetric(MatrixLowerTriangular&& matrix) noexcept
{
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = std::move(matrix);
}

MatrixSymmetric::~MatrixSymmetric()
{
	this->destroyL();
}

double MatrixSymmetric::operator()(const unsigned& rowIndex, const unsigned& columnIndex) const
{
	return (columnIndex > rowIndex) ? _matTri(columnIndex, rowIndex) : _matTri(rowIndex, columnIndex);
}


MatrixSymmetric& MatrixSymmetric::operator=(const MatrixSymmetric& matrix)
{
	if (!(this == &matrix)) {
		this->destroyL();
		_rowSize = matrix.getSize();
		_columnSize = matrix.getSize();
		_matTri = matrix._matTri;
	}

	return (*this);
}

MatrixSymmetric& MatrixSymmetric::operator=(MatrixSymmetric&& matrix) noexcept
{
	this->destroyL();
	_rowSize = matrix.getSize();
	_columnSize = matrix.getSize();
	_matTri = std::move(matrix._matTri);

	return (*this);
}

MatrixSymmetric MatrixSymmetric::operator+(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(this->getSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSymmetric MatrixSymmetric::operator-(const MatrixSymmetric& matrix) const
{
	MatrixSymmetric resp(this->getSize());
	this->minus(matrix, resp);

	return resp;
}

MatrixSymmetric MatrixSymmetric::operator*(const double& scalar) const
{
	MatrixSymmetric resp(this->getSize());

	for (unsigned i = 0; i < this->getSize(); i++)
		for (unsigned j = 0; j <= i; j++)
			resp.setValue((*this)(i, j) * scalar, i, j);

	return resp;
}

/**
 * @brief Informs the Cholesky factor of this matrix
 * @details Cholesky Factor of positive-define matrix \f$ A\f$ is a lower-triangular matrix \f$ L\f$ where
 *  \f[
 *		A=LL^T
 *  \f]
 *	@return Cholesky Factor
 *	@exception std::logic_error This matrix not Cholesky decomposable
 */
MatrixLowerTriangular& MatrixSymmetric::getCholeskyFactor()
{
	this->createL();
	this->decomposeToCholesky();

	return (*_choleskyFactor);
}

double MatrixSymmetric::determinant()
{
	if (this->isPositiveDefinite()) {
		const double resp = _choleskyFactor->determinant();
		return resp * resp;
	}
	return AbstractMatrixSymmetry::determinant();
}

MatrixSymmetric MatrixSymmetric::getInverseAsSymmetric()
{
	MatrixSymmetric resp(this->getInverse().extractLowerPart());
	return resp;
}

bool MatrixSymmetric::isInvertible()
{
	if (this->isPositiveDefinite())
		for (unsigned i = 0; i < this->getSize(); i++)
			if (putils::isZero((*_choleskyFactor)(i, i)))
				return false;

	return AbstractMatrixSymmetry::isInvertible();
}

/**
 * @brief 
 * @return 
*/
MatrixSquare MatrixSymmetric::getInverse()
{
	if (this->isPositiveDefinite()) {
		return _choleskyFactor->getTranspose().getInverse() * _choleskyFactor->getInverse();
	}
	return AbstractMatrixSymmetry::getInverse();
}

/**
 * @todo Testar esta funcao
 * @brief 
 * @param rhs 
 * @return 
*/
Vector MatrixSymmetric::linearSolve(const Vector& rhs)
{
	if (rhs.getSize() != this->getSize())
		throw
			std::logic_error(messages::RHS_NOT_COMP);


	if (this->isPositiveDefinite()) {

		if (!this->isInvertible()) throw std::logic_error(messages::MATRIX_SINGULAR);

		const Vector resp1(this->findSolutionByBackSubstitution(*_choleskyFactor, rhs));

		return this->findSolutionByBackSubstitution(_choleskyFactor->getTranspose(), resp1);

	}


	return AbstractMatrixSymmetry::linearSolve(rhs);
}

// According to Golub & Van Loan, "Matrix Computations", ISBN  9789380250755, p. 164.
bool MatrixSymmetric::isPositiveDefinite()
{
	try {
		this->decomposeToCholesky();
		return true;
	}
	catch (...) {
		return false;
	}
}
