#pragma once
#include "Matrix.h"



class WeightedMean
{
private:
	const Matrix* _matHistoric{nullptr};

	Matrix _matFreqColumn{60, 6};
	Vector _veqFreqTotal{ 60 };
	Vector _vecWeightedMean{6};
	bool _calcMean{false};

	Vector _guess{ 6 };

	void calcWeightedMean();
	void calcFreqTotal();
	void calcFreqColumn();

	Vector getRandomGuess() const;

public:
	explicit WeightedMean(const Matrix* matHistoric) : _matHistoric(matHistoric){
	}

	void setMatrixHistoric(const Matrix* matHistoric);
	const Vector& getWeightedMean();
	Vector getGuess();
	std::string getGuessAString();
};
