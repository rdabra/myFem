#pragma once

#include <mutex>
#include <thread>
#include "JobTaskProdMatrix.h"

class JobManagerProdMatrix
{
private:
	std::mutex _mutex;

public:
	const Matrix& _operandA;
	const Matrix& _operandB;
	Matrix& _result;
	std::vector<JobTaskProdMatrix> _tasks;
	unsigned _lastRowA{ 0 };
	unsigned _lastColumnB{ 0 };


	JobManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result)
		: _operandA{operandA},
		  _operandB{operandB},
		  _result{result}
	{
		for (unsigned i = 0; i < putils::NUM_THREADS; ++i) 
			_tasks.emplace_back(i, (*this));
	}

	void startJob();

	void notifyIdleness(unsigned identifier);
};
