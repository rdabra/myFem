#include "pch.h"

#include "MatrixTriangular.h"
#include "MatrixTriangular.cpp"

TEST(MatrixTriangular, TestEqualityOperator) {
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

	MatrixTriangular v(4, true);
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

TEST(MatrixTriangular, TestDotProduct) {
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

	MatrixTriangular v(4, false);
	v.setValue(1.5, 3, 3);
	v.setValue(4.5, 2, 2);
	v.setValue(5.5, 2, 3);
	v.setValue(7.5, 1, 1);
	v.setValue(8.5, 1, 2);
	v.setValue(9.5, 1, 3);
	v.setValue(10.5, 0, 0);
	v.setValue(11.5, 0, 1);
	v.setValue(12.5, 0, 2);
	v.setValue(13.5, 0, 3);

	double resp = z.dotProduct(v);

	MatrixTriangular z1(z);
	MatrixTriangular v1(v);

	z1.transpose();
	v1.transpose();
	double resp1 = z1.dotProduct(v1);



	EXPECT_TRUE(putils::areEqual(resp, 810.0));
	EXPECT_TRUE(putils::areEqual(resp1, 810.0));

}

TEST(MatrixTriangular, TestPlus) {
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

	MatrixTriangular v(4, false);
	v.setValue(10.5, 0, 0);
	v.setValue(11.5, 0, 1);
	v.setValue(12.5, 0, 2);
	v.setValue(13.5, 0, 3);
	v.setValue(7.5, 1, 1);
	v.setValue(8.5, 1, 2);
	v.setValue(9.5, 1, 3);
	v.setValue(10.5, 2, 2);
	v.setValue(11.5, 2, 3);
	v.setValue(12.5, 3, 3);

	MatrixSquare resp(4);
	resp.setValue(11.5, 0, 0);
	resp.setValue(11.5, 0, 1);
	resp.setValue(12.5, 0, 2);
	resp.setValue(13.5, 0, 3);

	resp.setValue(4.0, 1, 0);
	resp.setValue(12.5, 1, 1);
	resp.setValue(8.5, 1, 2);
	resp.setValue(9.5, 1, 3);

	resp.setValue(7.0, 2, 0);
	resp.setValue(8.0, 2, 1);
	resp.setValue(19.5, 2, 2);
	resp.setValue(11.5, 2, 3);

	resp.setValue(10.0, 3, 0);
	resp.setValue(11.0, 3, 1);
	resp.setValue(12.0, 3, 2);
	resp.setValue(25.5, 3, 3);

	MatrixTriangular resp2(4, true);
	resp2.setValue(2.0, 0, 0);
	resp2.setValue(8.0, 1, 0);
	resp2.setValue(10.0, 1, 1);
	resp2.setValue(14.0, 2, 0);
	resp2.setValue(16.0, 2, 1);
	resp2.setValue(18.0, 2, 2);
	resp2.setValue(20.0, 3, 0);
	resp2.setValue(22.0, 3, 1);
	resp2.setValue(24.0, 3, 2);
	resp2.setValue(26.0, 3, 3);

	MatrixTriangular resp3(4, true);
	resp3.setValue(2.0, 0, 0);
	resp3.setValue(8.0, 1, 0);
	resp3.setValue(10.0, 1, 1);
	resp3.setValue(14.0, 2, 0);
	resp3.setValue(16.0, 2, 1);
	resp3.setValue(18.0, 2, 2);
	resp3.setValue(20.0, 3, 0);
	resp3.setValue(22.0, 3, 1);
	resp3.setValue(24.0, 3, 2);
	resp3.setValue(26.0, 3, 3);

	MatrixTriangular resp4(4, false);
	resp4.setValue(21, 0, 0);
	resp4.setValue(23, 0, 1);
	resp4.setValue(25, 0, 2);
	resp4.setValue(27, 0, 3);
	resp4.setValue(15, 1, 1);
	resp4.setValue(17, 1, 2);
	resp4.setValue(19, 1, 3);
	resp4.setValue(21, 2, 2);
	resp4.setValue(23, 2, 3);
	resp4.setValue(25, 3, 3);

	
	MatrixSquare x1(4);
	z.plus(v, x1);
	MatrixSquare x2(z + v);
	MatrixTriangular z1(z);
	MatrixSquare z2(z + z);
	MatrixSquare v2(v + v);
	z.addBy(z);

	MatrixTriangular v1(v);
	MatrixSquare resp1(resp);
	z1.transpose();
	v1.transpose();
	resp1.transpose();


	EXPECT_TRUE(resp == x1);
	EXPECT_TRUE(resp == x2);
	EXPECT_TRUE(resp2 == z);
	EXPECT_TRUE(resp1 == z1 + v1);
	EXPECT_TRUE(resp3 == z2);
	EXPECT_TRUE(resp4 == v2);

}

TEST(MatrixTriangular, TestMinus) {
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

	MatrixTriangular v(4, false);
	v.setValue(10.5, 0, 0);
	v.setValue(11.5, 0, 1);
	v.setValue(12.5, 0, 2);
	v.setValue(13.5, 0, 3);

	v.setValue(7.5, 1, 1);
	v.setValue(8.5, 1, 2);
	v.setValue(9.5, 1, 3);

	v.setValue(10.5, 2, 2);
	v.setValue(11.5, 2, 3);

	v.setValue(12.5, 3, 3);

	Matrix resp(4, 4);
	resp.setValue(-9.5, 0, 0);
	resp.setValue(-11.5, 0, 1);
	resp.setValue(-12.5, 0, 2);
	resp.setValue(-13.5, 0, 3);

	resp.setValue(4.0, 1, 0);
	resp.setValue(-2.5, 1, 1);
	resp.setValue(-8.5, 1, 2);
	resp.setValue(-9.5, 1, 3);

	resp.setValue(7.0, 2, 0);
	resp.setValue(8.0, 2, 1);
	resp.setValue(-1.5, 2, 2);
	resp.setValue(-11.5, 2, 3);

	resp.setValue(10.0, 3, 0);
	resp.setValue(11.0, 3, 1);
	resp.setValue(12.0, 3, 2);
	resp.setValue(0.5, 3, 3);

	MatrixTriangular resp2(4, true);
	resp2.setValue(0.0, 0, 0);
	resp2.setValue(0.0, 1, 0);
	resp2.setValue(0.0, 1, 1);
	resp2.setValue(0.0, 2, 0);
	resp2.setValue(0.0, 2, 1);
	resp2.setValue(0.0, 2, 2);
	resp2.setValue(0.0, 3, 0);
	resp2.setValue(0.0, 3, 1);
	resp2.setValue(0.0, 3, 2);
	resp2.setValue(0.0, 3, 3);

	MatrixSquare x1(4);
	z.minus(v, x1);
	MatrixSquare x2(z - v);
	z.subtractBy(z);

	EXPECT_TRUE(resp == x1);
	EXPECT_TRUE(resp == x2);
	EXPECT_TRUE(resp2 == z);
}

TEST(MatrixTriangular, TestTimes) {
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

	MatrixTriangular v(4, false);
	v.setValue(1.5, 3, 3);
	v.setValue(4.5, 2, 2);
	v.setValue(5.5, 2, 3);
	v.setValue(7.5, 1, 1);
	v.setValue(8.5, 1, 2);
	v.setValue(9.5, 1, 3);
	v.setValue(10.5, 0, 0);
	v.setValue(11.5, 0, 1);
	v.setValue(12.5, 0, 2);
	v.setValue(13.5, 0, 3);

	Matrix resp(4, 4);
	resp.setValue(10.5, 0, 0);
	resp.setValue(11.5, 0, 1);
	resp.setValue(12.5, 0, 2);
	resp.setValue(13.5, 0, 3);

	resp.setValue(42.0, 1, 0);
	resp.setValue(83.5, 1, 1);
	resp.setValue(92.5, 1, 2);
	resp.setValue(101.5, 1, 3);

	resp.setValue(73.5, 2, 0);
	resp.setValue(140.5, 2, 1);
	resp.setValue(196.0, 2, 2);
	resp.setValue(220.0, 2, 3);

	resp.setValue(105.0, 3, 0);
	resp.setValue(197.5, 3, 1);
	resp.setValue(272.5, 3, 2);
	resp.setValue(325.0, 3, 3);

	MatrixTriangular resp2(4, true);
	resp2.setValue(2.0, 0, 0);
	resp2.setValue(8.0, 1, 0);
	resp2.setValue(10.0, 1, 1);
	resp2.setValue(14.0, 2, 0);
	resp2.setValue(16.0, 2, 1);
	resp2.setValue(18.0, 2, 2);
	resp2.setValue(20.0, 3, 0);
	resp2.setValue(22.0, 3, 1);
	resp2.setValue(24.0, 3, 2);
	resp2.setValue(26.0, 3, 3);

	MatrixSquare x1(4);
	z.times(v, x1);
	Matrix x2(z * v);

	MatrixTriangular x3(4, true);
	z.times(2.0, x3);
	Matrix x4(z * 2.0);
	z.multiplyBy(2.0);

	EXPECT_TRUE(resp == x1);
	EXPECT_TRUE(resp == x2);
	EXPECT_TRUE(resp2 == x3);
	EXPECT_TRUE(resp2 == x4);
	EXPECT_TRUE(resp2 == z);
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

	EXPECT_TRUE(putils::areEqual(z.frobeniusNorm(), 27.7488739));
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

	MatrixTriangular zz(z);

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

	EXPECT_TRUE(z == zz);
	EXPECT_TRUE(b == a);
	EXPECT_TRUE(c == z);
	EXPECT_TRUE(d == a);
	EXPECT_TRUE(e == z);
	EXPECT_TRUE(f == a);
}
