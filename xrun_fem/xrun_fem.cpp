// xrun_fem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "MatrixTriangular.h"


int main()
{
	MatrixTriangular z(4, false);
	z.setValue(1.0, 3, 3);
	z.setValue(4.0, 2, 2);
	z.setValue(5.0, 2, 3);
	z.setValue(7.0, 1, 1);
	z.setValue(8.0, 1, 2);
	z.setValue(9.0, 1, 3);
	z.setValue(10.0, 0, 0);
	z.setValue(11.0, 0, 1);
	z.setValue(12.0, 0, 2);
	z.setValue(13.0, 0, 3);


	for (unsigned int i = 0; i < 4; i++)
	{
		for (unsigned int j = 0; j < 4; j++)
			std::cout << z(i, j) << " ";
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
