#pragma once

#include <stdexcept>
#include "AbstractArray.h"
#include "Messages.h"
#include "utils.h"

class Matrix;

class Vector : public AbstractArray
{
private:
	std::vector <double> _vector;
	unsigned _size{ 0 };

public:
	Vector() = default;
	Vector(unsigned size);
	Vector(const Vector& vector);
	Vector(Vector&& vector) noexcept;
	virtual ~Vector() = default;
	unsigned getArrayDimension() const override { return 1; }
	unsigned getNumberOfElements() const override { return _size; }
	const double& operator()(const unsigned& index) const;
	void setValue(const double& value, const unsigned& index);
	const unsigned& getSize(void) const { return _size; }
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
	virtual void swapElements(const unsigned& elmIndexA, const unsigned& elmIndexB);
	double frobeniusNorm() const;
	virtual void fillRandomly(const double& min, const double& max);
	void copyElementsFrom(const Vector& vector);
	Matrix toColumnMatrix() const;
	Matrix toRowMatrix() const;

};
