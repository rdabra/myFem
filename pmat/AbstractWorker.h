#pragma once

class JobManagerProdMatrix;

class AbstractWorker
{
protected:
	bool _endTask{false};
	unsigned _identifier{0};
	JobManagerProdMatrix* _manager { nullptr };
	virtual void makeTask() const =0;


public:
	virtual ~AbstractWorker() = default;

	void startTask() const;
	void endTask();
};
