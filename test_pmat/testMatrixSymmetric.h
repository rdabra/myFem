#pragma once

#include "pch.h"

#include "MatrixSymmetric.h"
#include "MatrixSymmetric.cpp"

TEST(MatrixSymmetric, TestEqualityOperator) {
	MatrixSymmetric z(4,false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(4,false);
	v.setValue(1.0, 0, 0);
	v.setValue(4.0, 1, 0);
	v.setValue(5.0, 1, 1);
	v.setValue(7.0, 2, 0);
	v.setValue(8.0, 2, 1);
	v.setValue(9.0, 2, 2);
	v.setValue(10.0, 3, 0);
	v.setValue(11.0, 3, 1);
	v.setValue(12.0, 3, 2);
	v.setValue(13.0, 3, 3);

	EXPECT_TRUE(v == z);
}

TEST(MatrixSymmetric, TestDotProduct) {
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(4, false);
	v.setValue(1.5, 0, 0);
	v.setValue(4.5, 1, 0);
	v.setValue(5.5, 1, 1);
	v.setValue(7.5, 2, 0);
	v.setValue(8.5, 2, 1);
	v.setValue(9.5, 2, 2);
	v.setValue(10.5, 3, 0);
	v.setValue(11.5, 3, 1);
	v.setValue(12.5, 3, 2);
	v.setValue(13.5, 3, 3);

	double resp = z.dotProduct(v);

	EXPECT_TRUE(putils::areEqual(resp, 1330.0));

}

TEST(MatrixSymmetric, TestPlus) {
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(4, false);
	v.setValue(1.0, 0, 0);
	v.setValue(4.0, 1, 0);
	v.setValue(5.0, 1, 1);
	v.setValue(7.0, 2, 0);
	v.setValue(8.0, 2, 1);
	v.setValue(9.0, 2, 2);
	v.setValue(10.0, 3, 0);
	v.setValue(11.0, 3, 1);
	v.setValue(12.0, 3, 2);
	v.setValue(13.0, 3, 3);

	MatrixSymmetric resp(4, false);
	resp.setValue(2.0, 0, 0);
	resp.setValue(8.0, 1, 0);
	resp.setValue(10.0, 1, 1);
	resp.setValue(14.0, 2, 0);
	resp.setValue(16.0, 2, 1);
	resp.setValue(18.0, 2, 2);
	resp.setValue(20.0, 3, 0);
	resp.setValue(22.0, 3, 1);
	resp.setValue(24.0, 3, 2);
	resp.setValue(26.0, 3, 3);


	MatrixSymmetric r1(4, false);
	z.plus(v, r1);
	MatrixSymmetric r2(z + v);
	z.addBy(v);

	EXPECT_TRUE(resp == r1);
	EXPECT_TRUE(resp == r2);
	EXPECT_TRUE(resp == z);
}

TEST(MatrixSymmetric, TestMinus) {
	MatrixSymmetric z(4, false);
	z.setValue(2.0, 0, 0);
	z.setValue(8.0, 1, 0);
	z.setValue(10.0, 1, 1);
	z.setValue(14.0, 2, 0);
	z.setValue(16.0, 2, 1);
	z.setValue(18.0, 2, 2);
	z.setValue(20.0, 3, 0);
	z.setValue(22.0, 3, 1);
	z.setValue(24.0, 3, 2);
	z.setValue(26.0, 3, 3);

	MatrixSymmetric v(4, false);
	v.setValue(1.0, 0, 0);
	v.setValue(4.0, 1, 0);
	v.setValue(5.0, 1, 1);
	v.setValue(7.0, 2, 0);
	v.setValue(8.0, 2, 1);
	v.setValue(9.0, 2, 2);
	v.setValue(10.0, 3, 0);
	v.setValue(11.0, 3, 1);
	v.setValue(12.0, 3, 2);
	v.setValue(13.0, 3, 3);

	MatrixSymmetric resp(4, false);
	resp.setValue(1.0, 0, 0);
	resp.setValue(4.0, 1, 0);
	resp.setValue(5.0, 1, 1);
	resp.setValue(7.0, 2, 0);
	resp.setValue(8.0, 2, 1);
	resp.setValue(9.0, 2, 2);
	resp.setValue(10.0, 3, 0);
	resp.setValue(11.0, 3, 1);
	resp.setValue(12.0, 3, 2);
	resp.setValue(13.0, 3, 3);

	MatrixSymmetric r1(4, false);
	z.minus(v, r1);
	MatrixSymmetric r2(z - v);
	z.subtractBy(v);

	EXPECT_TRUE(resp == r1);
	EXPECT_TRUE(resp == r2);
	EXPECT_TRUE(resp == z);

}

TEST(MatrixSymmetric, TestTimes) {
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(4, false);
	v.setValue(2.0, 0, 0);
	v.setValue(5.0, 1, 0);
	v.setValue(6.0, 1, 1);
	v.setValue(8.0, 2, 0);
	v.setValue(9.0, 2, 1);
	v.setValue(10.0, 2, 2);
	v.setValue(11.0, 3, 0);
	v.setValue(12.0, 3, 1);
	v.setValue(13.0, 3, 2);
	v.setValue(14.0, 3, 3);

	MatrixSquare resp(4);
	resp.setValue(188.0, 0, 0);
	resp.setValue(212.0, 0, 1);
	resp.setValue(244.0, 0, 2);
	resp.setValue(290.0, 0, 3);

	resp.setValue(218.0, 1, 0);
	resp.setValue(254.0, 1, 1);
	resp.setValue(300.0, 1, 2);
	resp.setValue(362.0, 1, 3);

	resp.setValue(258.0, 2, 0);
	resp.setValue(308.0, 2, 1);
	resp.setValue(374.0, 2, 2);
	resp.setValue(458.0, 2, 3);

	resp.setValue(314.0, 3, 0);
	resp.setValue(380.0, 3, 1);
	resp.setValue(468.0, 3, 2);
	resp.setValue(580.0, 3, 3);

	MatrixSymmetric resp1(4, false);
	resp1.setValue(2.0, 0, 0);
	resp1.setValue(8.0, 1, 0);
	resp1.setValue(10.0, 1, 1);
	resp1.setValue(14.0, 2, 0);
	resp1.setValue(16.0, 2, 1);
	resp1.setValue(18.0, 2, 2);
	resp1.setValue(20.0, 3, 0);
	resp1.setValue(22.0, 3, 1);
	resp1.setValue(24.0, 3, 2);
	resp1.setValue(26.0, 3, 3);

	MatrixSquare r1(4);
	z.times(v, r1);
	MatrixSquare r2(z * v);
	MatrixSymmetric r3;
	r3 = z;

	r3.multiplyBy(2.0);

	EXPECT_TRUE(resp == r1);
	EXPECT_TRUE(resp == r2);
	EXPECT_TRUE(z * 2.0 == resp1);
	EXPECT_TRUE(r3 == resp1);

}

TEST(MatrixSymmetric, TestFrobenius)
{
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);



	EXPECT_TRUE(putils::areEqual(z.frobeniusNorm(), 35.55277767));

}

TEST(MatrixSymmetric, TestDeterminant)
{
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	EXPECT_TRUE(putils::areEqual(z.determinant(), -116.0));
}

TEST(MatrixSymmetric, TestTranspose)
{
	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(z);
	
	z.transpose();

	EXPECT_TRUE(v == z);
}

TEST(MatrixSymmetric, TestMisc)
{

	MatrixSymmetric z(4, false);
	z.setValue(1.0, 0, 0);
	z.setValue(4.0, 1, 0);
	z.setValue(5.0, 1, 1);
	z.setValue(7.0, 2, 0);
	z.setValue(8.0, 2, 1);
	z.setValue(9.0, 2, 2);
	z.setValue(10.0, 3, 0);
	z.setValue(11.0, 3, 1);
	z.setValue(12.0, 3, 2);
	z.setValue(13.0, 3, 3);

	MatrixSymmetric v(4, false);
	v.setValue(1.0, 0, 0);
	v.setValue(4.0, 1, 0);
	v.setValue(5.0, 1, 1);
	v.setValue(7.0, 2, 0);
	v.setValue(8.0, 2, 1);
	v.setValue(9.0, 2, 2);
	v.setValue(10.0, 3, 0);
	v.setValue(11.0, 3, 1);
	v.setValue(12.0, 3, 2);
	v.setValue(13.0, 3, 3);

	MatrixSymmetric resp(4, false);
	resp.setValue(1.0, 0, 0);
	resp.setValue(4.0, 1, 0);
	resp.setValue(5.0, 1, 1);
	resp.setValue(7.0, 2, 0);
	resp.setValue(8.0, 2, 1);
	resp.setValue(9.0, 2, 2);
	resp.setValue(10.0, 3, 0);
	resp.setValue(11.0, 3, 1);
	resp.setValue(12.0, 3, 2);
	resp.setValue(13.0, 3, 3);

	MatrixSymmetric resp1(2, false);
	resp1.setValue(0.0, 0, 0);
	resp1.setValue(0.0, 1, 0);
	resp1.setValue(0.0, 1, 1);

	
	MatrixSymmetric a;
	a = (std::move(z));

	v.reset(2,false);


	EXPECT_TRUE(a == resp);
	EXPECT_TRUE(v == resp1);

}
