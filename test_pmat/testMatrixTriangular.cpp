#include "pch.h"

#include "MatrixLowerTriangular.h"
#include "MatrixUpperTriangular.h"



	TEST(TestMatrixTriangular,TestEqualityOperator) {
		MatrixLowerTriangular z(4);
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

		MatrixLowerTriangular v(4);
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

	TEST(TestMatrixTriangular,TestDotProduct) {
		MatrixUpperTriangular z(4);
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

		MatrixUpperTriangular v(4);
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

		MatrixLowerTriangular z1(z.getTranspose());
		MatrixLowerTriangular v1(v.getTranspose());

		double resp1 = z1.dotProduct(v1);



		EXPECT_TRUE(putils::areEqual(resp, 810.0));
		EXPECT_TRUE(putils::areEqual(resp1, 810.0));

	}

	TEST(TestMatrixTriangular,TestPlus) {
		MatrixLowerTriangular z(4);
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

		MatrixUpperTriangular v(4);
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

		MatrixLowerTriangular resp2(4);
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

		MatrixLowerTriangular resp3(4);
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

		MatrixUpperTriangular resp4(4);
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
		MatrixLowerTriangular z1(z);
		MatrixSquare z2(z + z);
		MatrixSquare v2(v + v);
		z.addBy(z);

		MatrixUpperTriangular v1(v);
		MatrixSquare resp1(resp);
		MatrixUpperTriangular zz1(z1.getTranspose());
		MatrixLowerTriangular vv1(v1.getTranspose());

		resp1.transpose();
		v.addBy(v);


		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp2 == z);
		EXPECT_TRUE(resp1 == zz1 + vv1);
		EXPECT_TRUE(resp3 == z2);
		EXPECT_TRUE(resp4 == v2);
		EXPECT_TRUE(resp4 == v);

	}

	TEST(TestMatrixTriangular,TestMinus) {
		MatrixLowerTriangular z(4);
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

		MatrixUpperTriangular v(4);
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

		MatrixLowerTriangular resp2(4);
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

		MatrixUpperTriangular resp3(4);
		resp3.setValue(0.0, 0, 0);
		resp3.setValue(0.0, 0, 1);
		resp3.setValue(0.0, 0, 2);
		resp3.setValue(0.0, 0, 3);
		resp3.setValue(0.0, 1, 1);
		resp3.setValue(0.0, 1, 2);
		resp3.setValue(0.0, 1, 3);
		resp3.setValue(0.0, 2, 2);
		resp3.setValue(0.0, 2, 3);
		resp3.setValue(0.0, 3, 3);


		MatrixLowerTriangular zz(z);
		MatrixUpperTriangular vv(v);

		MatrixSquare x1(4);
		z.minus(v, x1);
		MatrixSquare x2(z - v);

		z.subtractBy(z);

		MatrixSquare x3(4);
		MatrixSquare x4(4);
		v.minus(v, x3);

		MatrixLowerTriangular vvv(v.getTranspose());
		vvv.minus(vvv, x4);

		MatrixSquare x5(4);
		v.minus(v, x5);

		MatrixSquare x6(vv - zz);

		vv.subtractBy(vv);


		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp2 == z);
		EXPECT_TRUE(resp2 == x3);
		EXPECT_TRUE(resp2 == x4);
		EXPECT_TRUE(resp2 == x5);
		EXPECT_TRUE(resp * -1.0 == x6);
		EXPECT_TRUE(resp3 == vv);

	}

	TEST(TestMatrixTriangular,TestTimes) {
		MatrixLowerTriangular z(4);
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

		MatrixUpperTriangular v(4);
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

		Vector w(4);
		w.setValue(1.0, 0);
		w.setValue(2.0, 1);
		w.setValue(3.0, 2);
		w.setValue(4.0, 3);

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

		MatrixLowerTriangular resp2(4);
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

		Matrix resp3(4, 4);
		resp3.setValue(279., 0, 0);
		resp3.setValue(306., 0, 1);
		resp3.setValue(274.5, 0, 2);
		resp3.setValue(175.5, 0, 3);

		resp3.setValue(184.5, 1, 0);
		resp3.setValue(210., 1, 1);
		resp3.setValue(190.5, 1, 2);
		resp3.setValue(123.5, 1, 3);

		resp3.setValue(86.5, 2, 0);
		resp3.setValue(96.5, 2, 1);
		resp3.setValue(106.5, 2, 2);
		resp3.setValue(71.5, 2, 3);

		resp3.setValue(15.0, 3, 0);
		resp3.setValue(16.5, 3, 1);
		resp3.setValue(18., 3, 2);
		resp3.setValue(19.5, 3, 3);


		Vector respVecLow(4);
		respVecLow.setValue(1.0, 0);
		respVecLow.setValue(14.0, 1);
		respVecLow.setValue(50.0, 2);
		respVecLow.setValue(120.0, 3);

		Vector respVecUp(4);
		respVecUp.setValue(125.0, 0);
		respVecUp.setValue(78.5, 1);
		respVecUp.setValue(35.5, 2);
		respVecUp.setValue(6.0, 3);

		MatrixUpperTriangular resp6(4);
		resp6.setValue(3., 3, 3);
		resp6.setValue(9., 2, 2);
		resp6.setValue(11., 2, 3);
		resp6.setValue(15., 1, 1);
		resp6.setValue(17, 1, 2);
		resp6.setValue(19, 1, 3);
		resp6.setValue(21, 0, 0);
		resp6.setValue(23, 0, 1);
		resp6.setValue(25, 0, 2);
		resp6.setValue(27, 0, 3);



		Vector low(z * w);
		Vector up(v * w);


		MatrixSquare x1(4);
		z.times(v, x1);
		MatrixSquare x2(z * v);
		MatrixSquare x5(v * z);

		MatrixLowerTriangular x3(4);
		z.times(2.0, x3);
		MatrixLowerTriangular x4(z * 2.0);
		z.multiplyBy(2.0);

		MatrixUpperTriangular x6(v * 2.0);
		v.multiplyBy(2.0);

		EXPECT_TRUE(resp == x1);
		EXPECT_TRUE(resp == x2);
		EXPECT_TRUE(resp2 == x3);
		EXPECT_TRUE(resp2 == x4);
		EXPECT_TRUE(resp2 == z);
		EXPECT_TRUE(resp3 == x5);
		EXPECT_TRUE(respVecLow == low);
		EXPECT_TRUE(respVecUp == up);
		EXPECT_TRUE(resp6 == x6);
		EXPECT_TRUE(resp6 == v);

	}

	TEST(TestMatrixTriangular,TestFrobenius)
	{
		MatrixLowerTriangular z(4);
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

		MatrixUpperTriangular v(4);
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

	TEST(TestMatrixTriangular,TestDeterminant)
	{
		MatrixLowerTriangular z(4);
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

	TEST(TestMatrixTriangular,TestTranspose)
	{
		MatrixLowerTriangular z(4);
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

		MatrixUpperTriangular zt(4);
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

		MatrixUpperTriangular zz(z.getTranspose());

		EXPECT_TRUE(zz == zt);
	}

	TEST(TestMatrixTriangular,TestMisc)
	{
		MatrixLowerTriangular z(4);
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

		MatrixLowerTriangular resp1(4);
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

		MatrixLowerTriangular resp2(4);
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


		MatrixLowerTriangular zz(z);

		MatrixLowerTriangular zzz(z);
		zzz.swapRowElements(2, 3, 0, 2);

		MatrixLowerTriangular zzzz(z);
		zzzz.swapColumnElements(1, 2, 2, 3);

		MatrixUpperTriangular a(z.getTranspose());

		MatrixUpperTriangular b(a);

		MatrixLowerTriangular t(z);

		MatrixLowerTriangular c(std::move(t));

		MatrixUpperTriangular d;
		d = a;
		MatrixLowerTriangular e;
		e = z;

		MatrixUpperTriangular t1(a);

		MatrixUpperTriangular f;
		f = std::move(t1);


		MatrixLowerTriangular ee(5);
		ee.fillRandomly(-1.0, 2.0);

		MatrixUpperTriangular eee(5);
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
