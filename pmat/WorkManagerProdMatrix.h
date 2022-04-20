#pragma once

#include <mutex>
#include "Matrix.h"
#include "AbstractWorkManager.h"

/**
 * @brief Manages the matrix product to be done by a group of workers that multiply a line by a column
*/
class WorkManagerProdMatrix final : public AbstractWorkManager
{
private:
	unsigned _lastRowA{0};
	unsigned _lastColumnB{0};
	unsigned _nWorkers{0};
	std::mutex _mutexSetValue;

	Matrix* _result;


protected:
	/**
	 * @brief Dispatches to a worker the next pair (line, column) to be multiplied or notifies the worker of the end of work
	 * @param identifier Number that uniquely identifies a worker
	*/
	void setTask(unsigned identifier) override;


public:
	const Matrix* _operandA;
	const Matrix* _operandB;


	WorkManagerProdMatrix(const Matrix& operandA, const Matrix& operandB, Matrix& result, unsigned nWorkers);
	~WorkManagerProdMatrix() override;

	void setResultValue(double value, unsigned rowIndex, unsigned columnIndex);

};
