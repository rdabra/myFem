#include "pch.h"
#include "Vector.h"


Vector::Vector(unsigned int size)
{
	_size = size;
	_vector.resize(_size);
}

Vector::Vector(const Vector& vector)
{
	_size = vector.getSize();
	_vector.resize(_size);
	for (unsigned int i = 0; i < _size; i++)
		_vector.push_back(vector(i));
}

Vector::Vector(Vector&& vector) noexcept
{
	_size = vector.getSize();
	_vector = std::move(vector._vector);
}

const double& Vector::operator()(const unsigned int& index) const
{
	if (index >= _size) throw std::out_of_range(messages::INDEX_OUT);

	return _vector[index];
}

void Vector::setValue(const double& coef, const unsigned int& index)
{
	_vector[index] = coef;
}

Vector& Vector::operator=(const Vector& vector)
{
	_size = vector.getSize();
	_vector.clear();
	_vector.reserve(_size);
	for (unsigned int i = 0; i < _size; i++)
		_vector.push_back(vector(i));

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
		for (unsigned int i = 0; i < _size; i++)
		{
			resp = putils::areEqual(_vector[i], vector(i));
			if (!resp) break;
		}
	}
	return resp;
}

void Vector::plus(const Vector& vector, Vector& resp) const
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);
	if (_size != resp.getSize()) throw std::length_error(messages::NONCOMPT_RESP);

	for (unsigned int i = 0; i < _size; i++)
		resp.setValue(_vector[i] + vector(i), i);
}

Vector Vector::operator+(const Vector& vector) const
{
	Vector resp(vector.getSize());
	this->plus(vector, resp);
	return resp;
}

void Vector::addBy(const Vector& vector)
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);

	for (unsigned int i = 0; i < _size; i++)
		(*this).setValue(_vector[i] + vector(i), i);

}

void Vector::minus(const Vector& vector, Vector& resp) const
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);
	if (_size != resp.getSize()) throw std::length_error(messages::NONCOMPT_RESP);

	for (unsigned int i = 0; i < _size; i++)
		resp.setValue(_vector[i] - vector(i), i);
}


Vector Vector::operator-(const Vector& vector) const
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);

	Vector resp(_size);
	this->minus(vector, resp);
	return resp;
}

void Vector::subtractBy(const Vector& vector)
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);

	for (unsigned int i = 0; i < _size; i++)
		this->setValue(_vector[i] - vector(i), i);
}


double Vector::dotProduct(const Vector& vector) const
{
	if (_size != vector.getSize()) throw std::length_error(messages::OPERANDS_EQUAL);

	double resp = 0.0;
	for (unsigned int i = 0; i < _size; i++)
		resp += _vector[i] * vector(i);

	return resp;
}

void Vector::times(const double& scalar, Vector& resp) const
{
	for (unsigned int i = 0; i < _size; i++)
		resp.setValue(scalar * _vector[i], i);
}

Vector Vector::operator*(const double& scalar) const
{
	Vector resp(_size);
	this->times(scalar, resp);
	return resp;
}

void Vector::multiplyBy(const double& scalar)
{
	for (unsigned int i = 0; i < _size; i++)
		this->setValue(scalar * _vector[i], i);
}

double Vector::frobeniusNorm() const
{
	double resp = 0.0;
	for (unsigned int i = 0; i < _size; i++)
		resp += _vector[i] * _vector[i];

	return sqrt(resp);
}

