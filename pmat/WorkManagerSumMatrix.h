#pragma once
#include <mutex>

#include "AbstractWorkManager.h"


/**
 * @brief Manages the matrix sum to be done by a group of workers that sum a row
*/
class WorkManagerSumMatrix final : public AbstractWorkManager
{
private:
	std::mutex _mutexSetValue;
	unsigned _lastRow{ 0 };
	unsigned _nWorkers{ 0 };

protected:
	void setTask(unsigned identifier) override;

public:
	const Matrix* _operandA;
	const Matrix* _operandB;
	Matrix* _result;

	WorkManagerSumMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result, unsigned nWorkers);
	~WorkManagerSumMatrix() override;

	void setResultValue(double value, unsigned rowIndex, unsigned columnIndex);

};
