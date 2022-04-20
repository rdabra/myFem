#pragma once

#include "AbstractWorker.h"
#include "WorkManagerProdMatrix.h"


class WorkManagerProdMatrix;

/**
 * @brief A worker that enables matrix multiplication
*/
class WorkerProdMatrix final : public AbstractWorker
{
private:
	unsigned _rowA{0};
	unsigned _columnB{0};

protected:
	void performTask() const override;

public:
	WorkerProdMatrix(unsigned identifier, WorkManagerProdMatrix& manager)
	{
		_identifier = identifier;
		_manager = &manager;
	}

	void setRowColumn(unsigned rowA, unsigned columnB);
};
