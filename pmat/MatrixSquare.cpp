#include "pch.h"
#include "MatrixSquare.h"
#include "MatrixLowerTriangular.h" // In order to define the class completely
#include "MatrixUpperTriangular.h" // In order to define the class completely
#include "MatrixSymmetric.h" // In order to define the class completely
#include "MatrixSkewSymmetric.h" // In order to define the class completely


/**
 * @brief Performs the partial pivoting process on upper matrix U
 * @param matU Matrix on which row swaps will be performed
 * @param idxPivot Specifies the pivot bellow which row swaps are performed
*/
void MatrixSquare::swapRowsBellow(MatrixSquare& matU, const unsigned& idxPivot)
{
	unsigned idxMax = idxPivot;
	double valMax = std::abs(matU(idxPivot, idxPivot));
	for (unsigned i = idxPivot + 1; i < matU.getSize(); i++)
		if (std::abs(matU(i, idxPivot)) > valMax) {
			valMax = std::abs(matU(i, idxPivot));
			idxMax = i;
		}

	if (idxMax != idxPivot) {
		matU.swapRows(idxMax, idxPivot);
		_matsPLU.matP->swapRows(idxMax, idxPivot);
		if (idxPivot > 0)
			_matsPLU.matL->partialSwapRows(idxMax, idxPivot, 0, idxPivot - 1);
		_matsPLU.swappedRows.emplace_back(idxMax, idxPivot);
		_changeSignForDet = !_changeSignForDet;
	}
}

void MatrixSquare::swapPivotColumn(MatrixSquare& partialR, const unsigned& idxPivot)
{
	double normMax{putils::ZERO};
	unsigned jMax{idxPivot};

	for (unsigned j = idxPivot; j < partialR.getSize(); ++j) {
		double normAux{putils::ZERO};
		for (unsigned i = 0; i < partialR.getSize(); ++i)
			normAux += partialR(i, j) * partialR(i, j);
		if (normAux > normMax) {
			normMax = normAux;
			jMax = j;
		}
	}

	if (jMax != idxPivot) {
		partialR.swapColumns(jMax, idxPivot);
		_matsQR.matP->swapColumns(jMax, idxPivot);
		_matsQR.swappedColumns.emplace_back(jMax, idxPivot);
	}
}

/**
 * @brief Performs the nullification of elements bellow the pivot
 * @param matU Matrix on which the nullification if performed
 * @param idxPivot Specifies the pivot bellow which nullification is performed
*/
void MatrixSquare::nullifyElementBellow(MatrixSquare& matU, const unsigned& idxPivot) const
{
	for (unsigned i = idxPivot + 1; i < matU.getSize(); i++) {
		_matsPLU.matL->setValue(matU(i, idxPivot) / matU(idxPivot, idxPivot), i, idxPivot);
		for (unsigned j = idxPivot; j < matU.getSize(); j++)
			matU.setValue(
				matU(i, j) - matU(idxPivot, j) * (*_matsPLU.matL)(i, idxPivot), i, j);
	}
}


void MatrixSquare::createLu()
{
	this->destroyLu();

	_matsPLU.matP = new MatrixSquare(this->getSize());
	_matsPLU.matU = new MatrixUpperTriangular(this->getSize());
	_matsPLU.matL = new MatrixLowerTriangular(this->getSize());
	_changeSignForDet = false;
	_calcLu = false;
	_calcStrictLu = false;

	for (unsigned j = 0; j < this->getSize(); j++) {
		_matsPLU.matL->setValue(putils::ONE, j, j);
		_matsPLU.matP->setValue(putils::ONE, j, j);
	}

	_createLu = true;
}

void MatrixSquare::destroyLu()
{
	if (_createLu) {
		delete _matsPLU.matL;
		delete _matsPLU.matP;
		delete _matsPLU.matU;
		_createLu = false;
		_calcStrictLu = false;
		_calcLu = false;
		_matsPLU.swappedRows.clear();
	}
}

void MatrixSquare::createSas()
{
	this->destroySas();

	_matsSAS.matS = new MatrixSymmetric(this->getSize());
	_matsSAS.matAS = new MatrixSkewSymmetric(this->getSize());
	_calcSas = false;

	_createSas = true;
}

void MatrixSquare::destroySas()
{
	if (_createSas) {
		delete _matsSAS.matS;
		delete _matsSAS.matAS;
		_createSas = false;
		_calcSas = false;
	}
}

void MatrixSquare::createQR()
{
	this->destroyQR();

	_matsQR.matP = new MatrixSquare(this->getSize());
	_matsQR.matQ = new MatrixSquare(this->getSize());
	_matsQR.matR = new MatrixUpperTriangular(this->getSize());
	_calcQR = false;
	_createQR = true;

	for (unsigned j = 0; j < this->getSize(); j++)
		_matsPLU.matP->setValue(putils::ONE, j, j);
}

void MatrixSquare::destroyQR()
{
	if (_createQR) {
		delete _matsQR.matP;
		delete _matsQR.matQ;
		delete _matsQR.matR;
		_createQR = false;
		_calcQR = false;
		_matsQR.swappedColumns.clear();
		_matsQR.rank = 0;
	}
}


MatrixSquare::~MatrixSquare()
{
	this->destroyLu();
	this->destroySas();
}

MatrixSquare MatrixSquare::toMatrixSquare() const
{
	return (*this);
}

MatrixSquare& MatrixSquare::operator=(const MatrixSquare& matrix)
{
	if (!(this == &matrix)) {
		this->destroyLu();
		this->destroySas();
		Matrix::operator=(matrix);
	}

	return (*this);
}

MatrixSquare& MatrixSquare::operator=(MatrixSquare&& matrix) noexcept
{
	this->destroyLu();
	this->destroySas();
	Matrix::operator=(std::move(matrix));
	return (*this);
}

MatrixSquare MatrixSquare::operator+(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->plus(matrix, resp);

	return resp;
}

MatrixSquare MatrixSquare::operator-(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->minus(matrix, resp);

	return resp;
}

MatrixSquare MatrixSquare::operator*(const MatrixSquare& matrix) const
{
	MatrixSquare resp(matrix.getSize());
	this->times(matrix, resp);

	return resp;
}

/**
 * @brief Calculates the multiplication of this matrix and the first parameter.
 * @details Given matrices \f$ A\f$ with size \f$ n\f$ and \f$ B\f$ with size \f$ m>n\f$, this function performs \f$A'.B\f$ 
 * of size \f$ m\f$ where \f$ A' = [A \quad 0; \quad 0 \quad 1] \f$ or  \f$ A' = [1 \quad 0; \quad 0 \quad A] \f$.
 * @param matrix The right operand, which must not be smaller
 * @param pos Position of this matrix on the matrix \f$A'\f$ (see details above)
 * @return The product of \f$A'\f$ and the parameter (see details above)
 * @exception std::logic_error Parameters are not compatible
*/
MatrixSquare MatrixSquare::multiplyByBiggerMatrix(const MatrixSquare& matrix, SubMatrixPos pos)
{
	if (matrix.getSize() < this->getSize()) throw std::logic_error(messages::NONCOMPT_ARG);

	MatrixSquare resp(matrix.getSize());

	const unsigned dif{matrix.getSize() - this->getSize()};
	const unsigned limInf{pos == SubMatrixPos::lower ? dif : 0};
	const unsigned limSup{pos == SubMatrixPos::lower ? matrix.getSize() : this->getSize()};

	for (unsigned i = 0; i < matrix.getSize(); ++i)
		for (unsigned j = 0; j < matrix.getSize(); ++j) {
			if (i < limInf || i >= limSup)
				resp.setValue(matrix(i, j), i, j);
			else {
				double aux{putils::ZERO};
				for (unsigned k = limInf; k < limSup; ++k)
					aux += (*this)(i - limInf, k - limInf) * matrix(k, j);
				resp.setValue(aux, i, j);
			}
		}

	return resp;
}

MatrixSquare MatrixSquare::operator*(const double& scalar) const
{
	MatrixSquare resp(this->getSize());
	this->times(scalar, resp);

	return resp;
}

void MatrixSquare::setValue(const double& value, const unsigned& rowIndex, const unsigned& columnIndex)
{
	Matrix::setValue(value, rowIndex, columnIndex);
	_calcLu = false;
	_calcStrictLu = false;
	_calcSas = false;
}

/**
 * @brief Calculates the trace of this matrix
 * @details Trace of \f$ A\f$ is calculated according to 
 *  \f[
 *		tr(A)=\sum_i A_{ii}
 *  \f]
 * @return The value of the trace
*/
double MatrixSquare::trace() const
{
	double resp = putils::ZERO;
	for (unsigned i = 0; i < this->getSize(); i++)
		resp += (*this)(i, i);
	return resp;
}


/**
 * @brief Performs the PLU decomposition
*/
void MatrixSquare::decomposeToPlu()
{
	if (!_calcLu) {
		this->createLu();
		MatrixSquare matU(this->toMatrixSquare());
		for (unsigned idxPivot = 0; idxPivot < matU.getSize() - 1; idxPivot++) {
			this->swapRowsBellow(matU, idxPivot);
			if (!putils::isZero(matU(idxPivot, idxPivot)))
				this->nullifyElementBellow(matU, idxPivot);
		}

		for (unsigned i = 0; i < matU.getSize(); ++i)
			for (unsigned j = i; j < matU.getSize(); ++j)
				_matsPLU.matU->setValue(matU(i, j), i, j);
		_calcLu = true;
	}
}


/**
 * @brief Performs the LU decomposition
*/
void MatrixSquare::decomposeToStrictLu()
{
	if (!_calcStrictLu) {
		this->createLu();
		MatrixSquare matU(*this);
		for (unsigned idxPivot = 0; idxPivot < matU.getSize() - 1; idxPivot++) {
			if (putils::isZero(matU(idxPivot, idxPivot))) {
				this->destroyLu();
				throw std::logic_error(messages::MATRIX_NOT_LU);
			}
			this->nullifyElementBellow(matU, idxPivot);
		}
		for (unsigned i = 0; i < matU.getSize(); ++i)
			for (unsigned j = i; j < matU.getSize(); ++j)
				_matsPLU.matU->setValue(matU(i, j), i, j);
		_calcStrictLu = true;
	}
}

/**
 * @brief Performs the symmetric-skew symmetric decomposition
*/
void MatrixSquare::decomposeToSas()
{
	if (!_calcSas) {
		this->createSas();
		for (unsigned i = 0; i < this->getSize(); ++i)
			for (unsigned j = 0; j <= i; ++j) {
				_matsSAS.matS->setValue(putils::ONE_HALF * ((*this)(i, j) + (*this)(j, i)), i, j);
				_matsSAS.matAS->setValue(putils::ONE_HALF * ((*this)(i, j) - (*this)(j, i)), i, j);
			}
		_calcSas = true;
	}
}

void MatrixSquare::decomposeToQR()
{
	if (!_calcQR) {
		this->createQR();

		MatrixSquare matQAux(this->calculateHouseholderSubMatrix((*this), 0));
		MatrixSquare matR(matQAux * (*this));

		for (unsigned idxPivot = 1; idxPivot < this->getSize() - 1; ++idxPivot) {
			MatrixSquare matHouseholder = this->calculateHouseholderSubMatrix(matR, idxPivot);
			matQAux = matHouseholder.multiplyByBiggerMatrix(matQAux, SubMatrixPos::lower);
			matR = matHouseholder.multiplyByBiggerMatrix(matR, SubMatrixPos::lower);
		}

		for (unsigned i = 0; i < this->getSize(); ++i)
			for (unsigned j = 0; j < this->getSize(); ++j) {
				_matsQR.matQ->setValue(matQAux(j, i), i, j);
				if (j >= i)
					_matsQR.matR->setValue(matR(i, j), i, j);

			}

		_calcQR = true;
	}
}

void MatrixSquare::decomposeToQRPivot()
{
	if (!_calcQR) {
		this->createQR();

		MatrixSquare A(*this);
		this->swapPivotColumn(A, 0);
		MatrixSquare matQAux(this->calculateHouseholderSubMatrix(A, 0));
		MatrixSquare matR(matQAux * A);

		for (unsigned idxPivot = 1; idxPivot < this->getSize() - 1; ++idxPivot) {
			this->swapPivotColumn(matR, idxPivot);
			MatrixSquare matHouseholder = this->calculateHouseholderSubMatrix(matR, idxPivot);
			matQAux = matHouseholder.multiplyByBiggerMatrix(matQAux, SubMatrixPos::lower);
			matR = matHouseholder.multiplyByBiggerMatrix(matR, SubMatrixPos::lower);
		}

		for (unsigned i = 0; i < this->getSize(); ++i) {
			if (! putils::isZero(matR(i, i))) _matsQR.rank++;
			for (unsigned j = 0; j < this->getSize(); ++j) {
				_matsQR.matQ->setValue(matQAux(j, i), i, j);
				if (j >= i)
					_matsQR.matR->setValue(matR(i, j), i, j);

			}
		}

		_calcQR = true;
	}
}


/**
 * @brief Calculates the inverse of a triangular matrix
 * @param matrix Matrix whose inverse is calculated
 * @param resp The inverse of the first parameter
*/
void MatrixSquare::findInverseByBackSubstitution(const AbstractMatrixTriangular* matrix,
                                                 AbstractMatrixTriangular* resp) const
{
	std::vector<unsigned> ids(matrix->getSize());

	if (matrix->isLower())
		for (unsigned k = 0; k < matrix->getSize(); k++) ids[k] = k;
	else
		for (unsigned k = 0; k < matrix->getSize(); k++) ids[k] = matrix->getSize() - k - 1;

	for (unsigned idxPivot = 0; idxPivot < matrix->getSize(); idxPivot++) {
		resp->setValue(putils::ONE / (*matrix)(ids[idxPivot], ids[idxPivot]), ids[idxPivot], ids[idxPivot]);
		for (unsigned i = idxPivot + 1; i < matrix->getSize(); i++) {
			double num{putils::ZERO};
			for (unsigned j = idxPivot; j < i; j++)
				num -= (*matrix)(ids[i], ids[j]) * (*resp)(ids[j], ids[idxPivot]);
			resp->setValue(num / (*matrix)(ids[i], ids[i]), ids[i], ids[idxPivot]);
		}
	}
}

/**
 * @brief Calculates the solution of a linear system where the matrix is triangular
 * @param matrix Triangular matrix on the left-hand side
 * @param rhs Righ-hand side vector
 * @return Solution of the linear system
*/
Vector MatrixSquare::findSolutionByBackSubstitution(const AbstractMatrixTriangular& matrix, const Vector& rhs) const
{
	Vector resp(rhs.getSize());

	std::vector<unsigned> ids(matrix.getSize());

	if (matrix.isLower())
		for (unsigned k = 0; k < matrix.getSize(); k++) ids[k] = k;
	else
		for (unsigned k = 0; k < matrix.getSize(); k++) ids[k] = matrix.getSize() - k - 1;

	resp.setValue(rhs(ids[0]) / matrix(ids[0], ids[0]), ids[0]);
	for (unsigned i = 1; i < matrix.getSize(); i++) {
		double num{rhs(ids[i])};
		for (unsigned j = 0; j < i; j++)
			num -= matrix(ids[i], ids[j]) * resp(ids[j]);
		resp.setValue(num / matrix(ids[i], ids[i]), ids[i]);
	}

	return resp;
}

// https://en.wikipedia.org/wiki/QR_decomposition
MatrixSquare MatrixSquare::calculateHouseholderSubMatrix(const MatrixSquare& partialR,
                                                         const unsigned idxPivot) const
{
	Vector u(partialR.getSize() - idxPivot);
	double alpha{putils::ZERO};
	for (unsigned i = idxPivot; i < partialR.getSize(); ++i) {
		alpha += partialR(i, idxPivot) * partialR(i, idxPivot);
		u.setValue(partialR(i, idxPivot), i - idxPivot);
	}
	alpha = -putils::ONE * putils::sgnOf(partialR(idxPivot, idxPivot)) * sqrt(alpha);
	u.setValue(u(0) - alpha, 0);

	const double squareNormU = u.dotProduct(u);
	MatrixSquare resp(u.getSize());
	for (unsigned i = 0; i < resp.getSize(); ++i) {
		if (putils::isZero(squareNormU))
			resp.setValue(putils::ONE, i, i);
		else
			for (unsigned j = 0; j < resp.getSize(); ++j) {
				if (i == j)
					resp.setValue(putils::ONE - putils::TWO * u(i) * u(j) / squareNormU, i, j);
				else
					resp.setValue(-putils::TWO * u(i) * u(j) / squareNormU, i, j);
			}
	}


	return resp;
}


/**
 * @brief Performs the PLU decomposition of this matrix
 * @details For every square matrix \f$ A\f$, it is possible to obtain \f$ PA = LU\f$, where \f$P\f$ is a permutation matrix,
 * \f$L\f$ is unit lower triangular and \f$U\f$ is upper triangular.
 * @return The results of the PLU decomposition process
*/
const D_PLU& MatrixSquare::getPLU()
{
	this->decomposeToPlu();


	return _matsPLU;
}

/**
 * @brief Performs the LU decomposition of this matrix, if possible.
 * @details For some square matrices \f$ A\f$, it is possible to obtain \f$ A = LU\f$, where
 * \f$L\f$ is unit lower triangular and \f$U\f$ is upper triangular,
 * @return The results of the LU decomposition
 * @exception std::logic_error This matrix is not LU decomposable
 */
const D_PLU& MatrixSquare::getStrictLU()
{
	this->decomposeToStrictLu();


	return _matsPLU;
}

/**
 * @brief Performs the symmetric-skew symmetric additive decomposition of this matrix
 * @details For every square matrix \f$ A\f$, it is possible to obtain \f$ A = A_S+A_A\f$, where \f$A_S=(A+A^T)/2\f$ is a symmetric matrix and
 * \f$A_A=(A-A^T)/2\f$ a skew symmetric matrix
 * @return Results of the symmetric-skew symmetric decomposition
*/
const D_SAS& MatrixSquare::getSAS()
{
	this->decomposeToSas();


	return _matsSAS;
}

const D_QR& MatrixSquare::getQR()
{
	this->decomposeToQRPivot();


	return _matsQR;
}


/**
 * @brief Informs if this matrix is LU decomposable
 * @see MatrixSquare::getStrictLU
 * @return True if this matrix is LU decomposable
*/
bool MatrixSquare::isStrictLUDecomposable()
{
	try {
		this->decomposeToStrictLu();
		return true;
	}
	catch (...) {
		return false;
	}
}

/**
 * @brief Informs if this matrix is invertible
 * @return True if this matrix is invertible
*/
bool MatrixSquare::isInvertible()
{
	this->decomposeToPlu();

	for (unsigned i = 0; i < this->getSize(); i++)
		if (putils::isZero((*_matsPLU.matU)(i, i)))
			return false;

	return true;
}

/**
 * @brief Extracts the lower part of this matrix
 * @return The lower part of this matrix as a triangular matrix
*/
MatrixLowerTriangular MatrixSquare::extractLowerPart() const
{
	MatrixLowerTriangular resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i)
		for (unsigned j = 0; j <= i; ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

/**
 * @brief Extracts the upper part of this matrix
 * @return The upper part of this matrix as a triangular matrix
*/
MatrixUpperTriangular MatrixSquare::extractUpperPart() const
{
	MatrixUpperTriangular resp(this->getSize());
	for (unsigned i = 0; i < this->getSize(); ++i)
		for (unsigned j = i; j < this->getSize(); ++j)
			resp.setValue((*this)(i, j), i, j);
	return resp;
}

/**
 * @brief Performs the inverse of this matrix, if possible
 * @return The inverse of this matrix
 * @exception std::logic_error This matrix is singular
*/
MatrixSquare MatrixSquare::getInverse()
{
	if (!this->isInvertible()) throw std::logic_error(messages::MATRIX_SINGULAR);

	MatrixUpperTriangular invU(this->getSize());
	this->findInverseByBackSubstitution(_matsPLU.matU, &invU);

	MatrixLowerTriangular invL(this->getSize());
	this->findInverseByBackSubstitution(_matsPLU.matL, &invL);

	MatrixSquare resp(invU * invL);

	/**
	 * Recovering adequate positions by swapping columns in reverse order of the swapped rows
	 */
	for (unsigned i = 1; i <= _matsPLU.swappedRows.size(); ++i) {
		auto& swappedRow = _matsPLU.swappedRows[_matsPLU.swappedRows.size() - i];
		resp.swapColumns(swappedRow.first, swappedRow.second);
	}

	return resp;
}

/**
 * @brief Finds the solution of the linear system where this matrix is on the left-hand side 
 * @param rhs Right-hand side of the linear system
 * @return The solution of the linear system
 * @exception std::logic_error This matrix is singular
 * @exception std::logic_error Right-hand side not compatible
*/
Vector MatrixSquare::linearSolve(const Vector& rhs)
{
	if (rhs.getSize() != this->getSize())
		throw
			std::logic_error(messages::RHS_NOT_COMP);

	if (!this->isInvertible()) throw std::logic_error(messages::MATRIX_SINGULAR);

	Vector aux(rhs);

	for (auto& swappedRow : _matsPLU.swappedRows)
		aux.swapElements(swappedRow.first, swappedRow.second);

	const Vector resp1(_matsPLU.matL->linearSolve(aux));

	return _matsPLU.matU->linearSolve(resp1);
}

/**
 * @brief Informs if this matrix is positive definite
 * @details Considering the PLU decomposition, a matrix is considered to be positive definite if every diagonal element of U is positive
 * @see MatrixSquare::getPLU
 * @see "Matrix Computations", Golub & Van Loan, ISBN  9789380250755, p. 161.
 * @return True if this matrix is positive definite
*/
bool MatrixSquare::isPositiveDefinite()
{
	if (this->isStrictLUDecomposable()) {
		for (unsigned i = 0; i < this->getSize(); i++)
			if ((*_matsPLU.matU)(i, i) <= 0) return false;
		return true;
	}

	return false;
}

/**
 * @brief Informs if this matrix is orthogonal
 * @details A matrix is orthogonal if its inverse equals its transpose
 * @return True if this matrix is orthogonal
*/
bool MatrixSquare::isOrthogonal()
{
	if (this->isInvertible()) {
		const MatrixSquare inv(this->getInverse());
		for (unsigned i = 0; i < this->getSize(); ++i)
			for (unsigned j = 0; j < this->getSize(); ++j)
				if (!putils::areEqual(inv(i, j), (*this)(j, i))) return false;
		return true;
	}
	return false;
}

unsigned MatrixSquare::rank() const
{
	unsigned resp{this->getSize()};

	if (_calcLu) {
		for (unsigned i = this->getSize(); i-- > 0;) {
			unsigned j{i};
			for (; j < this->getSize(); ++j)
				if (!putils::isZero((*_matsPLU.matU)(i, j)))
					break;
			if (j == this->getSize()) resp--;
		}
		return resp; //Quando implementar decomposição QR, remover essa linha
	} //Implementar decomposição QR (no processo dessa decomposicao, o rank é um dos resultados)

	return resp;
}

/**
 * @brief Calculates de determinant of this matrix
 * @details Determinant is calculated by previously performing a PLU decomposition
 * @return The determinant of this matrix
*/
double MatrixSquare::determinant()
{
	this->decomposeToPlu();

	double resp{putils::ONE};

	for (unsigned i = 0; i < this->getSize(); i++)
		resp *= (*_matsPLU.matU)(i, i);

	if (_changeSignForDet) resp = -resp;

	return resp;
}
