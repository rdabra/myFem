#pragma once

#include <stdexcept>
#include "Messages.h"
#include "utils.h"

class Vector
{
private:
	double* _vector;
	unsigned int _size;

public:
	Vector(unsigned int size);
	Vector(const Vector& vector);
	virtual ~Vector();
	const double& operator()(const unsigned int& index) const;
	void setValue(const double& coef, const unsigned int& index);
	const unsigned int& getSize(void) const { return _size; };
	Vector& operator=(const Vector&);
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
	double frobeniusNorm() const;
};

