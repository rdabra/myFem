#pragma once

class AbstractArray
{
public:
	virtual ~AbstractArray() = default;
	virtual unsigned getNumberOfElements() const =0;
	virtual unsigned getArrayDimension() const =0;
};
