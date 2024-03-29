// xrun_fem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "WorkManagerProdMatrix.h"
#include "Matrix.h"
#include <chrono> 

int main()
{


	/*
	Matrix A(1000, 1000);
	Matrix B(1000, 1000);
	Matrix R(1000, 1000);

	A.fillRandomly(-1.0, 1.0);
	B.fillRandomly(1.1, 2.1); 

	JobManagerProdMatrix man(A, B, R,5);

	std::cout << "threads: " << man.timeJob() << "ms\n";

	const auto t1 = std::chrono::high_resolution_clock::now();
	Matrix res(A * B);
	const auto t2 = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<double, std::milli> ms_double = t2 - t1;

	std::cout << "normal: " << ms_double.count() << "ms\n";
	*/

	//Type of random number distribution
	std::uniform_int_distribution<unsigned> dist(1, 60);

	//Mersenne Twister: Good quality random number generator initialized with non-deterministic seeds
	std::mt19937 rng(std::random_device{}());

		for (unsigned j = 0; j < 6; j++)
			std::cout << dist(rng) << "\n";

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
