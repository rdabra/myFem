#pragma once

class AbstractWorkManager;

/**
 * @brief A worker that performs tasks 
*/
class AbstractWorker
{
protected:
	bool _endOfWork{false};
	unsigned _identifier{0};
	AbstractWorkManager* _manager { nullptr };
	virtual void performTask() const =0;


public:
	virtual ~AbstractWorker() = default;

	void startTask() const;
	void notifyEndOfWork();
};
