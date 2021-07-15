#pragma once

#include "pch.h"

#include "MatrixSquare.h"
#include "MatrixSquare.cpp"


TEST(TestMatrixSquare, TestTrace) {
	MatrixSquare A(5);

	A.setValue(4.0, 0, 0);
	A.setValue(3.0, 0, 1);
	A.setValue(2.0, 0, 2);
	A.setValue(1.0, 0, 3);
	A.setValue(6.0, 0, 4);

	A.setValue(2.0, 1, 0);
	A.setValue(3.0, 1, 1);
	A.setValue(1.0, 1, 2);
	A.setValue(2.0, 1, 3);
	A.setValue(9.0, 1, 4);

	A.setValue(1.0, 2, 0);
	A.setValue(3.0, 2, 1);
	A.setValue(2.0, 2, 2);
	A.setValue(5.0, 2, 3);
	A.setValue(1.0, 2, 4);

	A.setValue(2.0, 3, 0);
	A.setValue(7.0, 3, 1);
	A.setValue(6.0, 3, 2);
	A.setValue(4.0, 3, 3);
	A.setValue(3.0, 3, 4);

	A.setValue(1.0, 4, 0);
	A.setValue(7.0, 4, 1);
	A.setValue(6.0, 4, 2);
	A.setValue(5.0, 4, 3);
	A.setValue(3.0, 4, 4);

	EXPECT_TRUE(A.trace() == 16.0);
}

TEST(TestMatrixSquare, TestDeterminant) {
	MatrixSquare A(4);

	A.setValue(1.0, 0, 0);
	A.setValue(2.0, 0, 1);
	A.setValue(3.0, 0, 2);
	A.setValue(4.0, 0, 3);

	A.setValue(1.0, 1, 0);
	A.setValue(3.0, 1, 1);
	A.setValue(2.0, 1, 2);
	A.setValue(5.0, 1, 3);

	A.setValue(2.0, 2, 0);
	A.setValue(1.0, 2, 1);
	A.setValue(6.0, 2, 2);
	A.setValue(3.0, 2, 3);

	A.setValue(3.0, 3, 0);
	A.setValue(2.0, 3, 1);
	A.setValue(1.0, 3, 2);
	A.setValue(1.0, 3, 3);


	MatrixSquare B(3);

	B.setValue(1.0, 0, 0);
	B.setValue(1.0, 0, 1);
	B.setValue(1.0, 0, 2);

	B.setValue(1.0, 1, 0);
	B.setValue(1.0, 1, 1);
	B.setValue(3.0, 1, 2);

	B.setValue(2.0, 2, 0);
	B.setValue(5.0, 2, 1);
	B.setValue(8.0, 2, 2);

	EXPECT_TRUE(putils::areEqual(A.determinant(), -3.0));
	EXPECT_TRUE(putils::areEqual(B.determinant(), -6.0));

}

TEST(TestMatrixSquare, TestMisc) {
	MatrixSquare A(4);

	A.setValue(1.0, 0, 0);
	A.setValue(2.0, 0, 1);
	A.setValue(3.0, 0, 2);
	A.setValue(4.0, 0, 3);

	A.setValue(1.0, 1, 0);
	A.setValue(3.0, 1, 1);
	A.setValue(2.0, 1, 2);
	A.setValue(5.0, 1, 3);

	A.setValue(2.0, 2, 0);
	A.setValue(1.0, 2, 1);
	A.setValue(6.0, 2, 2);
	A.setValue(3.0, 2, 3);

	A.setValue(3.0, 3, 0);
	A.setValue(2.0, 3, 1);
	A.setValue(1.0, 3, 2);
	A.setValue(1.0, 3, 3);


	MatrixSquare B;

	B = A;

	MatrixSquare T(B);

	MatrixSquare C;
	C = (std::move(T));

	EXPECT_TRUE(A == B);
	EXPECT_TRUE(A == C);

}

