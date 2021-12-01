#pragma once

#include <mutex>
#include <thread>
#include "Matrix.h"
#include "AbstractJobManager.h"
#include "WorkerProdMatrix.h"
#include "utils.h"

class JobManagerProdMatrix final : public AbstractJobManager
{
private:
	std::mutex _mutex;
	unsigned _lastRowA{ 0 };
	unsigned _lastColumnB{ 0 };
	unsigned _nWorkers{ 0 };

protected:
	void setTask(unsigned identifier) override;

public:
	const Matrix* _operandA;
	const Matrix* _operandB;
	Matrix* _result;

	JobManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result, unsigned nWorkers);
	~JobManagerProdMatrix() override;

};
