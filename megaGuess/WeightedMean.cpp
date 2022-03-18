#include "WeightedMean.h"

#include <iostream>
#include <string>

void WeightedMean::calcWeightedMean()
{
	if (!_calcMean) {
		Vector sumNumerator(6);
		Vector sumWeights(6);

		// Criar funcao na biblioteca para preencher com zero

		sumNumerator.setValue(0.0, 0);
		sumNumerator.setValue(0.0, 1);
		sumNumerator.setValue(0.0, 2);
		sumNumerator.setValue(0.0, 3);
		sumNumerator.setValue(0.0, 4);
		sumNumerator.setValue(0.0, 5);

		sumWeights.setValue(0.0, 0);
		sumWeights.setValue(0.0, 1);
		sumWeights.setValue(0.0, 2);
		sumWeights.setValue(0.0, 3);
		sumWeights.setValue(0.0, 4);
		sumWeights.setValue(0.0, 5);


		for (unsigned i = 0; i < 60; i++)
			for (unsigned j = 0; j < 6; j++) {
				const double weight = _veqFreqTotal(i) * _matFreqColumn(i, j);
				sumNumerator.setValue(sumNumerator(j) + (i * weight), j);
				sumWeights.setValue(sumWeights(j) + weight, j);
			}

		for (unsigned j = 0; j < 6; j++)
			_vecWeightedMean.setValue(sumNumerator(j) / sumWeights(j), j);
	}
	_calcMean = true;
}

void WeightedMean::calcFreqTotal()
{
	const auto total = _matHistoric->getRowSize() * 60.0000000000;

	for (unsigned i = 0; i < 60; i++) {
		double freq = 1000.00 * static_cast<double>(_matHistoric->getNumberOfOccurrences(i)) / total;
		_veqFreqTotal.setValue(freq, i);
	}
}

void WeightedMean::calcFreqColumn()
{
	const auto total = static_cast<double>(_matHistoric->getRowSize());
	for (unsigned i = 0; i < 60; i++)
		for (unsigned j = 0; j < 6; j++) {
			double freq = 1000.00 * static_cast<double>(_matHistoric->getNumberOfOccurrencesInColumn(j, i)) / total;
			_matFreqColumn.setValue(freq, i, j);
		}
}

Vector WeightedMean::getRandomGuess() const
{
	const std::uniform_int_distribution<unsigned> dist(1, 60);

	std::mt19937 rng(std::random_device{}());

	Vector resp(6);

	std::cout << "Trying to get a valid random guess.\n";

	unsigned j = 0;
	do {
		auto g = static_cast<double>(dist(rng));

		bool found = false;
		for (unsigned k = 0; k < j; k++) {
			found = putils::areEqual(g, resp(k));
			if (found) break;
		}

		if (!found) resp.setValue(g, j++);

	}
	while (j < 6);
		
	std::cout << "Valid random guess found.\n";

	return resp.getAscOrderedVector();
}

Vector WeightedMean::getGuess() 
{
	this->calcWeightedMean();

	Vector resp = this->getRandomGuess();
	const Vector vecUnitaryWeightedMean = _vecWeightedMean.getUnitaryVector();
	double arcCos { abs(resp.getUnitaryVector().dotProduct(vecUnitaryWeightedMean))};

	std::cout << "Trying to find a close guess.\n";

	while (arcCos < 0.7071067811865475) {
		resp = this->getRandomGuess();
		arcCos = abs(resp.getUnitaryVector().dotProduct(vecUnitaryWeightedMean));
		std::cout << "ArcCos "<< arcCos << "\n";
	}
	std::cout << "Close guess found.\n";

	for (unsigned i = 0; i < 6; i++)
		resp.setValue(round(resp(i)), i);

	return resp;
}

std::string WeightedMean::getGuessAString()
{
	std::string resp = "[ ";
	const Vector g = this->getGuess();
	for (unsigned i = 0; i < 6; i++)
		resp += std::to_string(g(i)) + " ";
	resp += "]\n";

	return resp;
}

void WeightedMean::setMatrixHistoric(const Matrix* matHistoric)
{
	_matHistoric = matHistoric;
	_calcMean = false;
}

const Vector& WeightedMean::getWeightedMean()
{
	this->calcWeightedMean();


	return _vecWeightedMean;
}
