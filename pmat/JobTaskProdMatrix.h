#pragma once

class JobManagerProdMatrix;

class JobTaskProdMatrix
{
private:
	bool _endTask{false};
	unsigned _identifier{0};
	JobManagerProdMatrix& _manager;
	unsigned _rowA{0};
	unsigned _columnB{0};

public:
	JobTaskProdMatrix(unsigned identifier, JobManagerProdMatrix& manager) : _identifier{identifier}, _manager{manager}
	{
	}

	void setRowColumn(unsigned rowA, unsigned columnB);
	void startTask() const;
	void endTask();
};
