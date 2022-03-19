// megaGuess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Matrix.h"
#include "WeightedMean.h"

int main()
{
	Matrix mat{2463, 6, R"(C:\myWorks\mega\resultados.csv)"};


	WeightedMean w(&mat, 50000);

	std::cout << "Weighted Mean: " << w.getWeightedMeanAsString();


	std::cout << "Guesses: " << "\n" << w.getGuessesAsString(3) << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
