#include "WeightedMean.h"

#include <iostream>
#include <string>

void WeightedMean::calcWeightedMean()
{
	if (!_calcMean) {

		Vector aux(_vecWeightedMean.getSize());

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

		this->calcFreqColumn();
		this->calcFreqTotal();

		for (unsigned i = 0; i < 60; i++)
			for (unsigned j = 0; j < 6; j++) {
				const double weight = _veqFreqTotal(i) * _matFreqColumn(i, j);
				sumNumerator.setValue(sumNumerator(j) + ((i + 1) * weight), j);
				sumWeights.setValue(sumWeights(j) + weight, j);
			}

		for (unsigned j = 0; j < 6; j++)
			aux.setValue(sumNumerator(j) / sumWeights(j), j);

		_vecWeightedMean.copyElementsFrom(aux.getAscOrderedVector());
	}
	_calcMean = true;
}

void WeightedMean::calcFreqTotal()
{
	const auto total = _matHistoric->getRowSize() * 6.0000000000;

	for (unsigned i = 0; i < 60; i++) {
		double freq = 1000.00 * static_cast<double>(_matHistoric->getNumberOfOccurrences(i + 1.0)) / total;
		_veqFreqTotal.setValue(freq, i);
	}
}

void WeightedMean::calcFreqColumn()
{
	const auto total = static_cast<double>(_matHistoric->getRowSize());
	for (unsigned i = 0; i < 60; i++)
		for (unsigned j = 0; j < 6; j++) {
			double freq = 1000.00 * static_cast<double>(_matHistoric->getNumberOfOccurrencesInColumn(j, i + 1.0)) /
				total;
			_matFreqColumn.setValue(freq, i, j);
		}
}

double WeightedMean::getMyNorm(const Vector& vec) const
{
	double resp {0.0};
	for (unsigned i = 0; i < 5; i++) {
		const double dif = vec(i + 1) - vec(i) ;
		resp += dif * dif;
	}

	return sqrt(resp);
}

Vector WeightedMean::getRandomGuess() const
{
	const std::uniform_int_distribution<unsigned> dist(1, 60);

	std::mt19937 rng(std::random_device{}());

	Vector resp(6);

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


	return resp.getAscOrderedVector();
}

Vector WeightedMean::getGuess()
{
	this->calcWeightedMean();


	double dif = 1.00;
	const double normWeighted = this->getMyNorm(_vecWeightedMean);
	Vector resp(6);
	for (unsigned k = 0; k < _nRandomGuesses; k++) {
		Vector g = this->getRandomGuess();
		const double aux = abs(this->getMyNorm(g) - normWeighted) / normWeighted;
		if (aux < dif) {
			dif = aux;
			resp.copyElementsFrom(g);
		}
	}


	for (unsigned i = 0; i < 6; i++)
		resp.setValue(round(resp(i)), i);

	return resp;
}

std::string WeightedMean::getGuessAsString()
{
	std::string resp = "[ ";
	const Vector g = this->getGuess();
	for (unsigned i = 0; i < 6; i++)
		resp += std::to_string(g(i)) + " ";
	resp += "]\n";

	return resp;
}

std::string WeightedMean::getGuessesAsString(const unsigned& nGuesses)
{
	std::string resp;
	for (unsigned i = 0; i < nGuesses; i++)
		resp += this->getGuessAsString();
	return resp;
}

std::string WeightedMean::getWeightedMeanAsString()
{
	std::string resp = "[ ";
	const Vector g = this->getWeightedMean();
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
