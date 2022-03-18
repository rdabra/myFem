#include "pch.h"
#include "Vector.h"
#include "Matrix.h"

/**
 * @brief Constructs the object by specifying the size
 * @param size   Vector size
*/
Vector::Vector(unsigned size)
{
	_size = size;
	_vector.resize(_size);
}

Vector::Vector(const Vector& vector)
{
	_size = vector.getSize();
	_vector.resize(_size);
	for (unsigned i = 0; i < _size; i++)
		this->setValue(vector(i), i);
}

Vector::Vector(Vector&& vector) noexcept
{
	_size = vector.getSize();
	_vector = std::move(vector._vector);
}

/**
 * @brief Returns an element value 
 * @param index Position 
 * @return Element value
 * @exception std::logic_error Index out of range
*/
const double& Vector::operator()(const unsigned& index) const
{
	if (index >= _size) throw std::logic_error(messages::INDEX_OUT);

	return _vector[index];
}


/**
 * @brief Sets a value for an element
 * @param value Value to be set
 * @param index Position
*/
void Vector::setValue(const double& value, const unsigned& index)
{
	_vector[index] = value;
}


Vector& Vector::operator=(const Vector& vector)
{
	_size = vector.getSize();
	_vector.clear();
	_vector.resize(_size);
	for (unsigned i = 0; i < _size; i++)
		this->setValue(vector(i), i);

	return (*this);
}

Vector& Vector::operator=(Vector&& vector) noexcept
{
	_size = vector._size;
	_vector = std::move(vector._vector);

	return (*this);
}

bool Vector::operator==(const Vector& vector) const
{
	bool resp = _size == vector.getSize();
	if (resp) {
		for (unsigned i = 0; i < _size; i++) {
			resp = putils::areEqual((*this)(i), vector(i));
			if (!resp) break;
		}
	}
	return resp;
}

/**
 * @brief Calculates the sum of this vector with the first parameter
 * @param vector The right operand
 * @param resp  The result of the sum
 * @exception std::logic_error Parameters are not compatible
*/
void Vector::plus(const Vector& vector, Vector& resp) const
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);
	if (_size != resp.getSize()) throw std::logic_error(messages::NONCOMPT_RESP);

	for (unsigned i = 0; i < _size; i++)
		resp.setValue((*this)(i) + vector(i), i);
}

/**
 * @brief Calculates the sum of this vector with the parameter
 * @param vector The right operand
 * @exception std::logic_error Parameters are not compatible
*/
Vector Vector::operator+(const Vector& vector) const
{
	Vector resp(vector.getSize());
	this->plus(vector, resp);
	return resp;
}

/**
 * @brief Sums the parameter to this vector
 * @param vector Parameter summed to this vector
 * @exception std::logic_error Parameter is not compatible
*/
void Vector::addBy(const Vector& vector)
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);

	for (unsigned i = 0; i < _size; i++)
		(*this).setValue((*this)(i) + vector(i), i);
}

/**
 * @brief Calculates the subtraction between this vector and the first parameter
 * @param vector The right operand
 * @param resp  The result of the subtraction
 * @exception std::logic_error Parameters are not compatible
*/
void Vector::minus(const Vector& vector, Vector& resp) const
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);
	if (_size != resp.getSize()) throw std::logic_error(messages::NONCOMPT_RESP);

	for (unsigned i = 0; i < _size; i++)
		resp.setValue((*this)(i) - vector(i), i);
}

/**
 * @brief Calculates the subtraction between this vector and the parameter
 * @param vector The right operand
 * @return The result of the subtraction
 * @exception std::logic_error Parameters are not compatible
*/
Vector Vector::operator-(const Vector& vector) const
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);

	Vector resp(_size);
	this->minus(vector, resp);
	return resp;
}

/**
 * @brief Subtracts the parameter from this vector
 * @param vector Parameter that subtracts this vector
 * @exception std::logic_error Parameter is not compatible
*/
void Vector::subtractBy(const Vector& vector)
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);

	for (unsigned i = 0; i < _size; i++)
		this->setValue((*this)(i) - vector(i), i);
}

/**
 * @brief Calculates the dot product of this vector with the parameter
 * @param vector The right operand
 * @details The dot product of vectors \f$ v\f$ and \f$ u\f$ is
 *  \f[
 *		v.u = \sum_{i}v_{i}u_{i}
 *  \f]
 * @return The result of the dot product
 * @exception std::logic_error Operands are not compatible
*/
double Vector::dotProduct(const Vector& vector) const
{
	if (_size != vector.getSize()) throw std::logic_error(messages::OPERANDS_EQUAL);

	double resp = 0.0;
	for (unsigned i = 0; i < _size; i++)
		resp += (*this)(i) * vector(i);

	return resp;
}

/**
 * @brief Calculates the multiplication of this vector and the first parameter
 * @param scalar The right operand
 * @param resp  The result of the multiplication
*/
void Vector::times(const double& scalar, Vector& resp) const
{
	for (unsigned i = 0; i < _size; i++)
		resp.setValue(scalar * (*this)(i), i);
}

/**
 * @brief Calculates the multiplication of this matrix and the parameter
 * @param scalar The right operand
 * @return The result of the multiplication
*/
Vector Vector::operator*(const double& scalar) const
{
	Vector resp(_size);
	this->times(scalar, resp);
	return resp;
}

/**
 * @brief Multiplies this matrix by the parameter
 * @param scalar Parameter that multiplies this matrix
*/
void Vector::multiplyBy(const double& scalar)
{
	for (unsigned i = 0; i < _size; i++)
		this->setValue(scalar * (*this)(i), i);
}

/**
 * @brief Swaps two elements of this vector
 * @param elmIndexA An index 
 * @param elmIndexB Another index
 * @exception std::logic_error Index out of bounds
*/
void Vector::swapElements(const unsigned& elmIndexA, const unsigned& elmIndexB)
{
	if (elmIndexA >= _size || elmIndexB >= _size) throw std::logic_error(messages::INDEX_OUT);

	_vector[elmIndexB] = std::exchange(_vector[elmIndexA], _vector[elmIndexB]);
}

/**
 * @brief Calculates the Frobenius Norm of this vector
 * @details Frobenius Norm of vector \f$ v\f$ is calculated from the dot product the following way:
 *  \f[
 *		\sqrt{v:v}
 *  \f]
 * @return The value of the Frobenius Norm
*/
double Vector::frobeniusNorm() const
{
	return sqrt(this->dotProduct(*this));
}

unsigned Vector::getNumberOfOccurrences(const double& value) const
{
	unsigned res{0};

	for (unsigned i = 0; i < this->getSize(); i++)
		if (putils::areEqual((*this)(i), value)) res++;

	return res;
}

Vector Vector::getUnitaryVector() const
{
	return {(*this) * (putils::ONE / this->frobeniusNorm())};
}

Vector Vector::getAscOrderedVector() const
{
	Vector resp(*this);

	for (unsigned pivot = 0; pivot < resp.getSize() - 1; pivot++)
		for (unsigned i = pivot + 1; i < resp.getSize(); i++)
			if (resp(pivot) > resp(i)) resp.swapElements(pivot, i);

	return resp;
}

Vector Vector::getDescOrderedVector() const
{
	Vector resp(*this);

	for (unsigned pivot = 0; pivot < resp.getSize() - 1; pivot++)
		for (unsigned i = pivot + 1; i < resp.getSize(); i++)
			if (resp(pivot) < resp(i)) resp.swapElements(pivot, i);

	return resp;

}

/**
 * @brief Fills this vector with random values
 * @param min Lower limit
 * @param max Upper limit
*/
void Vector::fillRandomly(const double& min, const double& max)
{
	//Type of random number distribution
	std::uniform_real_distribution<double> dist(min, max);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

	for (unsigned i = 0; i < this->getSize(); i++)
		this->setValue(dist(rng), i);
}

/**
 * @brief Copies the elements from the parameter to this vector
 * @param vector Matrix whose elements are copied from
 * @exception std::logic_error Parameter is not compatible
*/
void Vector::copyElementsFrom(const Vector& vector)
{
	if (_size != vector.getSize()) throw std::logic_error(messages::NONCOMPT_ARG);
	for (unsigned i = 0; i < this->getSize(); i++)
		this->setValue(vector(i), i);
}

Matrix Vector::toColumnMatrix() const
{
	Matrix resp(this->getSize(), 1);
	for (unsigned i = 0; i < this->getSize(); i++)
		resp.setValue((*this)(i), i, 0);
	return resp;
}

Matrix Vector::toRowMatrix() const
{
	Matrix resp(1, this->getSize());
	for (unsigned j = 0; j < this->getSize(); j++)
		resp.setValue((*this)(j), 0, j);
	return resp;
}
