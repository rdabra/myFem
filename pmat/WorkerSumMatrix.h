#pragma once
#include "AbstractWorker.h"
#include "JobManagerSumMatrix.h"

class JobManagerSumMatrix;

class WorkerSumMatrix : public AbstractWorker
{
private:
	unsigned _row{0};

protected:
	void makeTask() const override;

public:
	WorkerSumMatrix(unsigned identifier, JobManagerSumMatrix& manager)
	{
		_identifier = identifier;
		_manager = &manager;
	}

	void setRow(unsigned row);
};
