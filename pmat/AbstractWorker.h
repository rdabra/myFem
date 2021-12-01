#pragma once

class AbstractJobManager;

class AbstractWorker
{
protected:
	bool _endTask{false};
	unsigned _identifier{0};
	AbstractJobManager* _manager { nullptr };
	virtual void makeTask() const =0;


public:
	virtual ~AbstractWorker() = default;

	void startTask() const;
	void endTask();
};
