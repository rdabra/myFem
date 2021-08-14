#include "pch.h"

#include "Vector.h"




	TEST(TestVector, TestEqualityOperator) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		Vector z(7);
		z.setValue(1.0, 0);
		z.setValue(2.0, 1);
		z.setValue(3.0, 2);
		z.setValue(4.0, 3);
		z.setValue(5.0, 4);
		z.setValue(6.0, 5);
		z.setValue(7.0, 6);

		Vector y(7);
		y.setValue(1.0, 0);
		y.setValue(2.0, 1);
		y.setValue(4.0, 2);
		y.setValue(3.0, 3);
		y.setValue(5.0, 4);
		y.setValue(6.0, 5);
		y.setValue(7.0, 6);

		EXPECT_TRUE(v == z);
		EXPECT_FALSE(z == y);
	}

	TEST(TestVector, TestDotProduct) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		Vector z(7);
		z.setValue(7.0, 0);
		z.setValue(6.0, 1);
		z.setValue(5.0, 2);
		z.setValue(4.0, 3);
		z.setValue(3.0, 4);
		z.setValue(2.0, 5);
		z.setValue(1.0, 6);

		EXPECT_TRUE(v.dotProduct(z) == 84.0);
	}

	TEST(TestVector, TestPlus) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		Vector z(7);
		z.setValue(7.0, 0);
		z.setValue(6.0, 1);
		z.setValue(5.0, 2);
		z.setValue(4.0, 3);
		z.setValue(3.0, 4);
		z.setValue(2.0, 5);
		z.setValue(1.0, 6);

		Vector res(7);
		res.setValue(8.0, 0);
		res.setValue(8.0, 1);
		res.setValue(8.0, 2);
		res.setValue(8.0, 3);
		res.setValue(8.0, 4);
		res.setValue(8.0, 5);
		res.setValue(8.0, 6);

		Vector x1(7);
		v.plus(z, x1);
		const Vector& x2 = v + z;
		v.addBy(z);

		EXPECT_TRUE(res == x1);
		EXPECT_TRUE(res == x2);
		EXPECT_TRUE(res == v);
	}

	TEST(TestVector, TestMinus) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		Vector z(7);
		z.setValue(7.0, 0);
		z.setValue(6.0, 1);
		z.setValue(5.0, 2);
		z.setValue(4.0, 3);
		z.setValue(3.0, 4);
		z.setValue(2.0, 5);
		z.setValue(1.0, 6);

		Vector res(7);
		res.setValue(-6.0, 0);
		res.setValue(-4.0, 1);
		res.setValue(-2.0, 2);
		res.setValue(0.0, 3);
		res.setValue(2.0, 4);
		res.setValue(4.0, 5);
		res.setValue(6.0, 6);

		Vector x1(7);
		v.minus(z, x1);
		const Vector& x2 = v - z;
		v.subtractBy(z);

		EXPECT_TRUE(res == x1);
		EXPECT_TRUE(res == x2);
		EXPECT_TRUE(res == v);
	}

	TEST(TestVector, TestTimes) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		double scalar = 3.0;

		Vector res(7);
		res.setValue(3.0, 0);
		res.setValue(6.0, 1);
		res.setValue(9.0, 2);
		res.setValue(12.0, 3);
		res.setValue(15.0, 4);
		res.setValue(18.0, 5);
		res.setValue(21.0, 6);

		Vector x1(7);
		v.times(scalar, x1);
		const Vector& x2 = v * scalar;
		v.multiplyBy(scalar);

		EXPECT_TRUE(res == x1);
		EXPECT_TRUE(res == x2);
		EXPECT_TRUE(res == v);
	}

	TEST(TestVector, TestFrobenius) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		double frobV{ sqrt(v.dotProduct(v)) };


		EXPECT_TRUE(putils::areEqual(v.frobeniusNorm(), frobV));
	}


	TEST(TestVector, TestMisc) {
		Vector v(7);
		v.setValue(1.0, 0);
		v.setValue(2.0, 1);
		v.setValue(3.0, 2);
		v.setValue(4.0, 3);
		v.setValue(5.0, 4);
		v.setValue(6.0, 5);
		v.setValue(7.0, 6);

		Vector a(v);
		Vector b;
		b = v;
		Vector c;
		c = a * 2.0;

		Vector res(7);
		res.setValue(2.0, 0);
		res.setValue(4.0, 1);
		res.setValue(6.0, 2);
		res.setValue(8.0, 3);
		res.setValue(10.0, 4);
		res.setValue(12.0, 5);
		res.setValue(14.0, 6);


		Vector res1(7);
		res1.setValue(1.0, 0);
		res1.setValue(5.0, 1);
		res1.setValue(3.0, 2);
		res1.setValue(4.0, 3);
		res1.setValue(2.0, 4);
		res1.setValue(6.0, 5);
		res1.setValue(7.0, 6);

		Vector vv(v);

		vv.swapElements(1, 4);

		EXPECT_TRUE(a == v);
		EXPECT_TRUE(b == v);
		EXPECT_TRUE(c == res);
		EXPECT_TRUE(vv == res1);

	}
