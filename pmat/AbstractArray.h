#pragma once

class AbstractArray
{
public:
	virtual unsigned getNumberOfElements() const =0;
	virtual unsigned getArrayDimension() const =0;
};
