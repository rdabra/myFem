#pragma once
#include "AbstractWorker.h"
#include "WorkManagerSumMatrix.h"

class WorkManagerSumMatrix;

/**
 * @brief A worker that enables matrix sum
*/
class WorkerSumMatrix : public AbstractWorker
{
private:
	unsigned _row{0};

protected:
	void performTask() const override;

public:
	WorkerSumMatrix(unsigned identifier, WorkManagerSumMatrix& manager)
	{
		_identifier = identifier;
		_manager = &manager;
	}

	/**
	 * @brief Specifies the rows to be summed
	 * @param rowIndex Rows to be summed
	*/
	void setRow(unsigned rowIndex);
};
