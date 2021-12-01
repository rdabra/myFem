#pragma once

#include "AbstractWorker.h"
class JobManagerProdMatrix;

class WorkerProdMatrix final : public AbstractWorker
{
private:
	unsigned _rowA{0};
	unsigned _columnB{0};

protected:
	void makeTask() const override;

public:
	WorkerProdMatrix(unsigned identifier, JobManagerProdMatrix& manager) 
	{
		_identifier = identifier;
		_manager = &manager;
	}

	void setRowColumn(unsigned rowA, unsigned columnB);
};
