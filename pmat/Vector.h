#pragma once

#include <stdexcept>
#include "Messages.h"
#include "utils.h"

class Vector
{
private:
	std::vector <double> _vector;
	unsigned int _size{ 0 };

public:
	Vector() {};
	Vector(unsigned int size);
	Vector(const Vector& vector);
	Vector(Vector&& vector) noexcept;
	virtual ~Vector() {};
	const double& operator()(const unsigned int& index) const;
	void setValue(const double& coef, const unsigned int& index);
	const unsigned int& getSize(void) const { return _size; };
	Vector& operator=(const Vector& vector);
	Vector& operator=(Vector&& vector) noexcept;
	bool operator==(const Vector& vector) const;
	double dotProduct(const Vector& vector) const;
	void plus(const Vector& vector, Vector& resp) const;
	Vector operator+(const Vector& vector) const;
	void addBy(const Vector& vector);
	void minus(const Vector& vector, Vector& resp) const;
	Vector operator-(const Vector& vector) const;
	void subtractBy(const Vector& vector);
	void times(const double& scalar, Vector& resp) const;
	Vector operator*(const double& scalar) const;
	void multiplyBy(const double& scalar);
	virtual void swapElements(const unsigned int& elmIndexA, const unsigned int& elmIndexB);
	double frobeniusNorm() const;
};
