// xrun_fem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "JobManagerProdMatrix.h"
#include "Matrix.h"
#include <chrono>

int main()
{
	Matrix A(1000, 1000);
	Matrix B(1000, 1000);
	Matrix R(1000, 1000);

	A.fillRandomly(-1.0, 1.0);
	B.fillRandomly(1.1, 2.0);

	JobManagerProdMatrix man(A, B, R);
	auto t1 = std::chrono::high_resolution_clock::now();
	man.startJob(5);
	auto t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> ms_double = t2 - t1;

	std::cout << "threads: " << ms_double.count() << "ms\n";


	t1 = std::chrono::high_resolution_clock::now();
	Matrix res(A*B);
	t2 = std::chrono::high_resolution_clock::now();

	ms_double = t2 - t1;

	std::cout << "normal: " << ms_double.count() << "ms\n";

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
