#include "pch.h"

#include "MatrixDiagonal.h"





	TEST(TestMatrixDiagonal, TestDeterminant) {
		MatrixDiagonal A(4);

		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 1, 1);
		A.setValue(3.0, 2, 2);
		A.setValue(4.0, 3, 3);


		MatrixSquare C(3);

		EXPECT_TRUE(putils::areEqual(A.getDeterminant(), 24.0));
		EXPECT_TRUE(A.isInvertible());
		EXPECT_FALSE(C.isInvertible());
	}

	TEST(TestMatrixDiagonal, TestDecompPLU) {
		MatrixDiagonal A(4);

		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 1, 1);
		A.setValue(3.0, 2, 2);
		A.setValue(4.0, 3, 3);


		MatrixDiagonal B(3);


		B.setValue(2.0, 0, 0);
		B.setValue(4.0, 1, 1);
		B.setValue(7.0, 2, 2);


		D_PLU mats = A.getPLU();

		MatrixSquare PA((*mats.matP) * A);
		MatrixSquare LU((*mats.matL) * (*mats.matU));

		D_PLU mats1 = B.getPLU();

		MatrixSquare PB((*mats1.matP) * B);
		MatrixSquare LU1((*mats1.matL) * (*mats1.matU));

		D_PLU mats2 = A.getStrictLU();

		MatrixSquare LU2((*mats2.matL) * (*mats2.matU));


		EXPECT_TRUE(PA == LU);
		EXPECT_TRUE(PB == LU1);
		EXPECT_TRUE(A == LU2);

	}


	TEST(TestMatrixDiagonal, TestInverse) {

		MatrixDiagonal A(4);

		A.setValue(1.0, 0, 0);
		A.setValue(3.0, 1, 1);
		A.setValue(2.0, 2, 2);
		A.setValue(5.0, 3, 3);


		MatrixDiagonal invA(4);

		invA.setValue(1.0, 0, 0);
		invA.setValue(1.0 / 3.0, 1, 1);
		invA.setValue(1.0 / 2.0, 2, 2);
		invA.setValue(1.0 / 5.0, 3, 3);



		EXPECT_TRUE(A.getInverse() == invA);
		EXPECT_TRUE(A.getInverse() == A.asMatrixSquare().getInverse());


	}



	TEST(TestMatrixDiagonal, TestPlus) {

		MatrixDiagonal z(4);

		z.setValue(1.0, 0, 0);
		z.setValue(3.0, 1, 1);
		z.setValue(2.0, 2, 2);
		z.setValue(5.0, 3, 3);


		MatrixDiagonal resp(4);
		resp.setValue(2.0, 0, 0);
		resp.setValue(6.0, 1, 1);
		resp.setValue(4.0, 2, 2);
		resp.setValue(10.0, 3, 3);


		MatrixDiagonal x1(4);
		z.plus(z, x1);
		MatrixDiagonal x2(z + z);
		z.addBy(z);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp == z);
	}

	TEST(TestMatrixDiagonal, TestMinus) {

		MatrixDiagonal z(4);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 1, 1);
		z.setValue(3.0, 2, 2);
		z.setValue(4.0, 3, 3);


		MatrixDiagonal resp(4);


		MatrixDiagonal x1(4);
		z.minus(z, x1);
		MatrixDiagonal x2(z - z);
		z.subtractBy(z);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp == z);
	}


	TEST(TestMatrixDiagonal, TestTimes) {
		MatrixDiagonal z(4);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 1, 1);
		z.setValue(3.0, 2, 2);
		z.setValue(4.0, 3, 3);

		MatrixDiagonal v(4);
		v.setValue(-1.0, 0, 0);
		v.setValue(-2.0, 1, 1);
		v.setValue(-3.0, 2, 2);
		v.setValue(-4.0, 3, 3);

		MatrixSquare resp(4);
		resp.setValue(-1.0, 0, 0);
		resp.setValue(-4.0, 1, 1);
		resp.setValue(-9.0, 2, 2);
		resp.setValue(-16.0, 3, 3);

		MatrixSquare resp1(4);
		resp1.setValue(2.0, 0, 0);
		resp1.setValue(4.0, 1, 1);
		resp1.setValue(6.0, 2, 2);
		resp1.setValue(8.0, 3, 3);


		EXPECT_TRUE(resp == z * v);
		EXPECT_TRUE(resp1 == z * 2.0);

	}


	TEST(TestMatrixDiagonal, TestMisc) {
		MatrixDiagonal A(4);

		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 1, 1);
		A.setValue(3.0, 2, 2);
		A.setValue(4.0, 3, 3);

		MatrixLowerTriangular ALower(4);
		MatrixUpperTriangular AUpper(4);

		ALower.setValue(1.0, 0, 0);
		ALower.setValue(2.0, 1, 1);
		ALower.setValue(3.0, 2, 2);
		ALower.setValue(4.0, 3, 3);

		AUpper.setValue(1.0, 0, 0);
		AUpper.setValue(2.0, 1, 1);
		AUpper.setValue(3.0, 2, 2);
		AUpper.setValue(4.0, 3, 3);

		MatrixDiagonal B;
		B = A;

		MatrixDiagonal C(B);

		MatrixDiagonal CC;
		CC = std::move(C);

		EXPECT_TRUE(A.extractLowerPart() == ALower);
		EXPECT_TRUE(A.extractUpperPart() == AUpper);
		EXPECT_TRUE(B == A);
		EXPECT_TRUE(CC == B);
	}

	TEST(TestMatrixDiagonal, TestPositiveDefinite) {
		MatrixDiagonal A(4);
		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 1, 1);
		A.setValue(3.0, 2, 2);
		A.setValue(4.0, 3, 3);

		MatrixDiagonal B(4);
		B.setValue(1.0, 0, 0);
		B.setValue(-2.0, 1, 1);
		B.setValue(3.0, 2, 2);
		B.setValue(4.0, 3, 3);

		EXPECT_TRUE(A.isPositiveDefinite());
		EXPECT_FALSE(B.isPositiveDefinite());

	}


	TEST(TestMatrixDiagonal, TestSymmetricAntiSym) {

		MatrixDiagonal A(4);
		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 1, 1);
		A.setValue(3.0, 2, 2);
		A.setValue(4.0, 3, 3);

		D_SAS matSas = A.getSAS();

		EXPECT_TRUE(*matSas.matAS + *matSas.matS == A);

	}

