#pragma once
#include <mutex>

#include "AbstractJobManager.h"


class JobManagerSumMatrix final : public AbstractJobManager
{
private:
	std::mutex _mutex;
	unsigned _lastRow{ 0 };
	unsigned _nWorkers{ 0 };

protected:
	void setTask(unsigned identifier) override;

public:
	const Matrix* _operandA;
	const Matrix* _operandB;
	Matrix* _result;

	JobManagerSumMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result, unsigned nWorkers);
	~JobManagerSumMatrix() override;


};
