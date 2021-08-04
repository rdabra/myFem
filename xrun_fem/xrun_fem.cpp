// xrun_fem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "MatrixSquare.h"
#include "AbstractMatrixSymAntiSym.h"


int main()
{

	MatrixSquare z(2);
	z.setValue(1.0, 0, 0);
	z.setValue(3.0, 0, 1);
	z.setValue(2.0, 1, 0);
	z.setValue(4.0, 1, 1);

	D_SAS matSas = z.getSAS();


	for (unsigned i = 0; i < matSas.matS->getSize(); ++i) {
		for (unsigned j = 0; j < matSas.matS->getSize(); ++j)
			std::cout << (*matSas.matS)(i, j) << " ";
		std::cout << "\n";
	}

	std::cout << "\n";
	
	for (unsigned i = 0; i < matSas.matS->getSize(); ++i) {
		for (unsigned j = 0; j < matSas.matS->getSize(); ++j)
			std::cout << (*matSas.matAS)(i, j) << " ";
		std::cout << "\n";
	}

	std::cout << "\n";
	
	MatrixSquare x((*matSas.matAS) + (*matSas.matS));
	for (unsigned i = 0; i < matSas.matS->getSize(); ++i) {
		for (unsigned j = 0; j < matSas.matS->getSize(); ++j)
			std::cout << x(i, j) << " ";
		std::cout << "\n";
	}


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
