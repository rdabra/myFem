#pragma once

#include "pch.h"

#include "MatrixSymmetric.h"
#include "MatrixSymmetric.cpp"

TEST(MatrixSymmetric, TestEqualityOperator) {
	MatrixSymmetric z(4);
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

	MatrixSymmetric v(4);
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
	MatrixSymmetric z(4);
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

	MatrixSymmetric v(4);
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

	EXPECT_TRUE(putils::areEqual(resp, 810.0));

}

TEST(MatrixSymmetric, TestPlus) {
	MatrixSymmetric z(4);
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

	MatrixSymmetric v(4);
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

	MatrixSymmetric resp(4);
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


	MatrixSymmetric r1(4);
	z.plus(v, r1);
	MatrixSymmetric r2(z + v);
	z.addBy(v);

	EXPECT_TRUE(resp == r1);
	EXPECT_TRUE(resp == r2);
	EXPECT_TRUE(resp == z);
}

TEST(MatrixSymmetric, TestMinus) {
	MatrixSymmetric z(4);
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

	MatrixSymmetric v(4);
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

	MatrixSymmetric resp(4);
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

	MatrixSymmetric r1(4);
	z.minus(v, r1);
	MatrixSymmetric r2(z - v);
	z.subtractBy(v);

	EXPECT_TRUE(resp == r1);
	EXPECT_TRUE(resp == r2);
	EXPECT_TRUE(resp == z);

}

TEST(MatrixSymmetric, TestTimes) {
	MatrixSymmetric z(4);
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

	MatrixSymmetric v(4);
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

	MatrixSymmetric resp1(4);
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


//	EXPECT_TRUE(resp == x1);
//	EXPECT_TRUE(resp == x2);
//	EXPECT_TRUE(resp2 == x3);
//	EXPECT_TRUE(resp2 == x4);
//	EXPECT_TRUE(resp2 == z);
//	EXPECT_TRUE(resp3 == x5);
//	EXPECT_TRUE(respVconcoecLow == low);
//	EXPECT_TRUE(respVecUp == up);
//	EXPECT_TRUE(resp6 == x6);
//	EXPECT_TRUE(resp6 == v);

}

TEST(MatrixTriangular, TestFrobenius)
{
	MatrixTriangular z(4, true);
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

	double frobZ{ sqrt(z.dotProduct(z)) };

	MatrixTriangular v(4, false);
	v.setValue(1.0, 3, 3);
	v.setValue(4.0, 2, 2);
	v.setValue(5.0, 2, 3);
	v.setValue(7.0, 1, 1);
	v.setValue(8.0, 1, 2);
	v.setValue(9.0, 1, 3);
	v.setValue(10.0, 0, 0);
	v.setValue(11.0, 0, 1);
	v.setValue(12.0, 0, 2);
	v.setValue(13.0, 0, 3);

	double frobV{ sqrt(v.dotProduct(v)) };


	EXPECT_TRUE(putils::areEqual(z.frobeniusNorm(), frobZ));
	EXPECT_TRUE(putils::areEqual(v.frobeniusNorm(), frobV));

}

TEST(MatrixTriangular, TestDeterminant)
{
	MatrixTriangular z(4, true);
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

	EXPECT_TRUE(putils::areEqual(z.determinant(), 585.0));
}

TEST(MatrixTriangular, TestTranspose)
{
	MatrixTriangular z(4, true);
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

	MatrixTriangular zt(4, false);
	zt.setValue(1.0, 0, 0);
	zt.setValue(4.0, 0, 1);
	zt.setValue(5.0, 1, 1);
	zt.setValue(7.0, 0, 2);
	zt.setValue(8.0, 1, 2);
	zt.setValue(9.0, 2, 2);
	zt.setValue(10.0, 0, 3);
	zt.setValue(11.0, 1, 3);
	zt.setValue(12.0, 2, 3);
	zt.setValue(13.0, 3, 3);

	z.transpose();

	EXPECT_TRUE(z == zt);
}

TEST(MatrixTriangular, TestMisc)
{
	MatrixTriangular z(4, true);
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

	MatrixTriangular resp1(4, true);
	resp1.setValue(1.0, 0, 0);
	resp1.setValue(4.0, 1, 0);
	resp1.setValue(5.0, 1, 1);
	resp1.setValue(10.0, 2, 0);
	resp1.setValue(11.0, 2, 1);
	resp1.setValue(12.0, 2, 2);
	resp1.setValue(7.0, 3, 0);
	resp1.setValue(8.0, 3, 1);
	resp1.setValue(9.0, 3, 2);
	resp1.setValue(13.0, 3, 3);

	MatrixTriangular resp2(4, true);
	resp2.setValue(1.0, 0, 0);
	resp2.setValue(4.0, 1, 0);
	resp2.setValue(5.0, 1, 1);
	resp2.setValue(7.0, 2, 0);
	resp2.setValue(9.0, 2, 1);
	resp2.setValue(8.0, 2, 2);
	resp2.setValue(10.0, 3, 0);
	resp2.setValue(12.0, 3, 1);
	resp2.setValue(11.0, 3, 2);
	resp2.setValue(13.0, 3, 3);


	MatrixTriangular zz(z);

	MatrixTriangular zzz(z);
	zzz.swapRowElements(2, 3, 0, 2);

	MatrixTriangular zzzz(z);
	zzzz.swapColumnElements(1, 2, 2, 3);

	MatrixTriangular a(z);
	a.transpose();

	MatrixTriangular b(a);

	MatrixTriangular t(z);

	MatrixTriangular c(std::move(t));

	MatrixTriangular d;
	d = a;
	MatrixTriangular e;
	e = z;

	MatrixTriangular t1(a);

	MatrixTriangular f;
	f = std::move(t1);


	MatrixTriangular ee(5, true);
	ee.fillRandomly(-1.0, 2.0);

	MatrixTriangular eee(5, false);
	eee.fillRandomly(-1.0, 2.0);


	EXPECT_TRUE(z == zz);
	EXPECT_TRUE(b == a);
	EXPECT_TRUE(c == z);
	EXPECT_TRUE(d == a);
	EXPECT_TRUE(e == z);
	EXPECT_TRUE(f == a);
	EXPECT_TRUE(resp1 == zzz);
	EXPECT_TRUE(resp2 == zzzz);
	EXPECT_TRUE(ee(2, 2) < 2.0 && ee(2, 2) > -1.0);
	EXPECT_TRUE(eee(2, 2) < 2.0 && eee(2, 2) > -1.0);

}
