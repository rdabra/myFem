#include "pch.h"

#include "WorkManagerProdMatrix.h"
#include "Matrix.h"

TEST(TestMatrix, TestEqualityOperator) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Matrix v(4, 3);
		v.setValue(1.0, 0, 0);
		v.setValue(2.0, 0, 1);
		v.setValue(3.0, 0, 2);
		v.setValue(4.0, 1, 0);
		v.setValue(5.0, 1, 1);
		v.setValue(6.0, 1, 2);
		v.setValue(7.0, 2, 0);
		v.setValue(8.0, 2, 1);
		v.setValue(9.0, 2, 2);
		v.setValue(10.0, 3, 0);
		v.setValue(11.0, 3, 1);
		v.setValue(12.0, 3, 2);

		EXPECT_TRUE(v == z);
	}

	TEST(TestMatrix, TestDotProduct) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Matrix v(4, 3);
		v.setValue(1.0, 0, 0);
		v.setValue(2.0, 0, 1);
		v.setValue(3.0, 0, 2);
		v.setValue(4.0, 1, 0);
		v.setValue(5.0, 1, 1);
		v.setValue(6.0, 1, 2);
		v.setValue(7.0, 2, 0);
		v.setValue(8.0, 2, 1);
		v.setValue(9.0, 2, 2);
		v.setValue(10.0, 3, 0);
		v.setValue(11.0, 3, 1);
		v.setValue(12.0, 3, 2);

		double resp = z.dotProduct(v);
		EXPECT_TRUE(putils::areEqual(resp, 650.0));
	}

	TEST(TestMatrix, TestPlus) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Matrix v(4, 3);
		v.setValue(1.0, 0, 0);
		v.setValue(2.0, 0, 1);
		v.setValue(3.0, 0, 2);
		v.setValue(4.0, 1, 0);
		v.setValue(5.0, 1, 1);
		v.setValue(6.0, 1, 2);
		v.setValue(7.0, 2, 0);
		v.setValue(8.0, 2, 1);
		v.setValue(9.0, 2, 2);
		v.setValue(10.0, 3, 0);
		v.setValue(11.0, 3, 1);
		v.setValue(12.0, 3, 2);

		Matrix resp(4, 3);
		resp.setValue(2.0, 0, 0);
		resp.setValue(4.0, 0, 1);
		resp.setValue(6.0, 0, 2);
		resp.setValue(8.0, 1, 0);
		resp.setValue(10.0, 1, 1);
		resp.setValue(12.0, 1, 2);
		resp.setValue(14.0, 2, 0);
		resp.setValue(16.0, 2, 1);
		resp.setValue(18.0, 2, 2);
		resp.setValue(20.0, 3, 0);
		resp.setValue(22.0, 3, 1);
		resp.setValue(24.0, 3, 2);

		Matrix x1(4, 3);
		z.plus(v, x1);
		Matrix x2(z + v);
		z.addBy(v);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp == z);
	}

	TEST(TestMatrix, TestMinus) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Matrix v(4, 3);
		v.setValue(12.0, 0, 0);
		v.setValue(11.0, 0, 1);
		v.setValue(10.0, 0, 2);
		v.setValue(9.0, 1, 0);
		v.setValue(8.0, 1, 1);
		v.setValue(7.0, 1, 2);
		v.setValue(6.0, 2, 0);
		v.setValue(5.0, 2, 1);
		v.setValue(4.0, 2, 2);
		v.setValue(3.0, 3, 0);
		v.setValue(2.0, 3, 1);
		v.setValue(1.0, 3, 2);

		Matrix resp(4, 3);
		resp.setValue(-11.0, 0, 0);
		resp.setValue(-9.0, 0, 1);
		resp.setValue(-7.0, 0, 2);
		resp.setValue(-5.0, 1, 0);
		resp.setValue(-3.0, 1, 1);
		resp.setValue(-1.0, 1, 2);
		resp.setValue(1.0, 2, 0);
		resp.setValue(3.0, 2, 1);
		resp.setValue(5.0, 2, 2);
		resp.setValue(7.0, 3, 0);
		resp.setValue(9.0, 3, 1);
		resp.setValue(11.0, 3, 2);

		Matrix x1(4, 3);
		z.minus(v, x1);
		Matrix x2(z - v);
		z.subtractBy(v);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp == z);
	}

	TEST(TestMatrix, TestTimes) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Vector u(3);
		u.setValue(3.0, 0);
		u.setValue(2.0, 1);
		u.setValue(-1.0, 2);


		Matrix v(3, 4);
		v.setValue(1.0, 0, 0);
		v.setValue(2.0, 0, 1);
		v.setValue(3.0, 0, 2);
		v.setValue(4.0, 0, 3);
		v.setValue(5.0, 1, 0);
		v.setValue(6.0, 1, 1);
		v.setValue(7.0, 1, 2);
		v.setValue(8.0, 1, 3);
		v.setValue(9.0, 2, 0);
		v.setValue(10.0, 2, 1);
		v.setValue(11.0, 2, 2);
		v.setValue(12.0, 2, 3);

		Matrix resp(4, 4);
		resp.setValue(38.0, 0, 0);
		resp.setValue(44.0, 0, 1);
		resp.setValue(50.0, 0, 2);
		resp.setValue(56.0, 0, 3);
		resp.setValue(83.0, 1, 0);
		resp.setValue(98.0, 1, 1);
		resp.setValue(113.0, 1, 2);
		resp.setValue(128.0, 1, 3);
		resp.setValue(128.0, 2, 0);
		resp.setValue(152.0, 2, 1);
		resp.setValue(176.0, 2, 2);
		resp.setValue(200.0, 2, 3);
		resp.setValue(173.0, 3, 0);
		resp.setValue(206.0, 3, 1);
		resp.setValue(239.0, 3, 2);
		resp.setValue(272.0, 3, 3);

		Matrix resp2(4, 3);
		resp2.setValue(2.0, 0, 0);
		resp2.setValue(4.0, 0, 1);
		resp2.setValue(6.0, 0, 2);
		resp2.setValue(8.0, 1, 0);
		resp2.setValue(10.0, 1, 1);
		resp2.setValue(12.0, 1, 2);
		resp2.setValue(14.0, 2, 0);
		resp2.setValue(16.0, 2, 1);
		resp2.setValue(18.0, 2, 2);
		resp2.setValue(20.0, 3, 0);
		resp2.setValue(22.0, 3, 1);
		resp2.setValue(24.0, 3, 2);

		Vector resp3(4);
		resp3.setValue(4.0, 0);
		resp3.setValue(16.0, 1);
		resp3.setValue(28.0, 2);
		resp3.setValue(40.0, 3);

		Vector x5 = z * u;

		Matrix x1(4, 4);
		z.times(v, x1);
		Matrix x2(z * v);

		Matrix respp(4, 4);
		WorkManagerProdMatrix manag(z, v, respp, 5);
		manag.startWork();

		Matrix x3(4, 3);
		z.times(2.0, x3);
		Matrix x4(z * 2.0);
		z.multiplyBy(2.0);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp == respp);
		EXPECT_TRUE(resp2 == x3);
		EXPECT_TRUE(resp2 == x4);
		EXPECT_TRUE(resp2 == z);
		EXPECT_TRUE(resp3 == x5);

	}

	TEST(TestMatrix, TestFrobenius) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		double frobZ{ sqrt(z.dotProduct(z)) };


		EXPECT_TRUE(putils::areEqual(z.getFrobeniusNorm(), frobZ));
	}


	TEST(TestMatrix, TestHadamard) {
		Matrix A(4, 3);
		A.setValue(1.0, 0, 0);
		A.setValue(2.0, 0, 1);
		A.setValue(3.0, 0, 2);
		A.setValue(4.0, 1, 0);
		A.setValue(5.0, 1, 1);
		A.setValue(6.0, 1, 2);
		A.setValue(7.0, 2, 0);
		A.setValue(8.0, 2, 1);
		A.setValue(9.0, 2, 2);
		A.setValue(10.0, 3, 0);
		A.setValue(11.0, 3, 1);
		A.setValue(12.0, 3, 2);

		Matrix B(4, 3);
		B.setValue(1.0, 0, 0);
		B.setValue(2.0, 0, 1);
		B.setValue(2.0, 0, 2);
		B.setValue(3.0, 1, 0);
		B.setValue(2.0, 1, 1);
		B.setValue(1.0, 1, 2);
		B.setValue(2.0, 2, 0);
		B.setValue(3.0, 2, 1);
		B.setValue(4.0, 2, 2);
		B.setValue(2.0, 3, 0);
		B.setValue(10.0, 3, 1);
		B.setValue(100.0, 3, 2);

		Matrix C(4, 3);
		C.setValue(1.0, 0, 0);
		C.setValue(4.0, 0, 1);
		C.setValue(6.0, 0, 2);
		C.setValue(12.0, 1, 0);
		C.setValue(10.0, 1, 1);
		C.setValue(6.0, 1, 2);
		C.setValue(14.0, 2, 0);
		C.setValue(24.0, 2, 1);
		C.setValue(36.0, 2, 2);
		C.setValue(20.0, 3, 0);
		C.setValue(110.0, 3, 1);
		C.setValue(1200.0, 3, 2);



		EXPECT_TRUE(C==A.multiplyHadamardBy(B));
	}


	TEST(TestMatrix, TestTranspose) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);


		Matrix zt(3, 4);
		zt.setValue(1.0, 0, 0);
		zt.setValue(2.0, 1, 0);
		zt.setValue(3.0, 2, 0);
		zt.setValue(4.0, 0, 1);
		zt.setValue(5.0, 1, 1);
		zt.setValue(6.0, 2, 1);
		zt.setValue(7.0, 0, 2);
		zt.setValue(8.0, 1, 2);
		zt.setValue(9.0, 2, 2);
		zt.setValue(10.0, 0, 3);
		zt.setValue(11.0, 1, 3);
		zt.setValue(12.0, 2, 3);

		z.transpose();

		EXPECT_TRUE(zt == z);
	}

	TEST(TestMatrix, TestOccurences) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(8.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(9.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(10.0, 3, 1);
		z.setValue(9.0, 3, 2);


		EXPECT_TRUE(z.getNumberOfOccurrences(8.0) == 2);
		EXPECT_TRUE(z.getNumberOfOccurrences(58.0) == 0);
		EXPECT_TRUE(z.getNumberOfOccurrencesInColumn(2,9.0) == 3);
		EXPECT_TRUE(z.getNumberOfOccurrencesInRow(3, 10.0) == 2);

	}


	TEST(TestMatrix, TestMisc) {
		Matrix z(4, 3);
		z.setValue(1.0, 0, 0);
		z.setValue(2.0, 0, 1);
		z.setValue(3.0, 0, 2);
		z.setValue(4.0, 1, 0);
		z.setValue(5.0, 1, 1);
		z.setValue(6.0, 1, 2);
		z.setValue(7.0, 2, 0);
		z.setValue(8.0, 2, 1);
		z.setValue(9.0, 2, 2);
		z.setValue(10.0, 3, 0);
		z.setValue(11.0, 3, 1);
		z.setValue(12.0, 3, 2);

		Matrix a;
		a = z;

		Matrix b;
		b = z * 1.0;


		Matrix v(4, 3);
		v.setValue(3.0, 0, 0);
		v.setValue(1.0, 0, 1);
		v.setValue(2.0, 0, 2);
		v.setValue(-4.0, 1, 0);
		v.setValue(3.0, 1, 1);
		v.setValue(1.0, 1, 2);
		v.setValue(1.0, 2, 0);
		v.setValue(0.0, 2, 1);
		v.setValue(3.0, 2, 2);
		v.setValue(2.0, 3, 0);
		v.setValue(1.0, 3, 1);
		v.setValue(6.0, 3, 2);


		Matrix resp(4, 3);
		resp.setValue(3.0, 0, 0);
		resp.setValue(1.0, 0, 1);
		resp.setValue(2.0, 0, 2);
		resp.setValue(-8.0, 1, 0);
		resp.setValue(6.0, 1, 1);
		resp.setValue(2.0, 1, 2);
		resp.setValue(1.0, 2, 0);
		resp.setValue(0.0, 2, 1);
		resp.setValue(3.0, 2, 2);
		resp.setValue(2.0, 3, 0);
		resp.setValue(1.0, 3, 1);
		resp.setValue(6.0, 3, 2);

		Matrix resp1(4, 3);
		resp1.setValue(3.0, 0, 0);
		resp1.setValue(2.0, 0, 1);
		resp1.setValue(2.0, 0, 2);
		resp1.setValue(-8.0, 1, 0);
		resp1.setValue(12.0, 1, 1);
		resp1.setValue(2.0, 1, 2);
		resp1.setValue(1.0, 2, 0);
		resp1.setValue(0.0, 2, 1);
		resp1.setValue(3.0, 2, 2);
		resp1.setValue(2.0, 3, 0);
		resp1.setValue(2.0, 3, 1);
		resp1.setValue(6.0, 3, 2);

		Matrix resp2(4, 3);
		resp2.setValue(3.0, 0, 1);
		resp2.setValue(2.0, 0, 0);
		resp2.setValue(2.0, 0, 2);
		resp2.setValue(-8.0, 1, 1);
		resp2.setValue(12.0, 1, 0);
		resp2.setValue(2.0, 1, 2);
		resp2.setValue(1.0, 2, 1);
		resp2.setValue(0.0, 2, 0);
		resp2.setValue(3.0, 2, 2);
		resp2.setValue(2.0, 3, 1);
		resp2.setValue(2.0, 3, 0);
		resp2.setValue(6.0, 3, 2);

		v.multiplyRowBy(1, 2.0);

		Matrix c = v;

		c.multiplyColumnBy(1, 2.0);

		Matrix d = c;

		d.swapColumns(0, 1);

		Matrix e(5, 5);
		e.fillRandomly(-1.0, 2.0);


		EXPECT_TRUE(a == z);
		EXPECT_TRUE(b == z);
		EXPECT_TRUE(resp == v);
		EXPECT_TRUE(resp1 == c);
		EXPECT_TRUE(resp2 == d);
		EXPECT_TRUE(e(2, 2) < 2.0 && e(2, 2) > -1.0);


	}

