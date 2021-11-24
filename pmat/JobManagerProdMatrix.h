#pragma once

#include <mutex>
#include <thread>
#include "Matrix.h"
#include "JobTaskProdMatrix.h"
#include "utils.h"

class JobManagerProdMatrix
{
private:
	std::mutex _mutex;
	std::vector<JobTaskProdMatrix> _tasks;
	unsigned _lastRowA{ 0 };
	unsigned _lastColumnB{ 0 };

public:
	const Matrix& _operandA;
	const Matrix& _operandB;
	Matrix& _result;


	JobManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result)
		: _operandA{operandA},
		  _operandB{operandB},
		  _result{result}
	{
	}

	void startJob(const unsigned nWorkers);

	void notifyIdleness(unsigned identifier);
};
