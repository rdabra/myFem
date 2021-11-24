#pragma once

namespace putils
{
	//tolerância até à qtde de casas decimais
	static double DIF_TOLERANCE = 0.0000000001;

	static double ZERO = 0.0000000000;

	static double ONE = 1.0000000000;

	static double TWO = 2.0000000000;

	static double MINUS_ONE = -1.0000000000;

	static double ONE_HALF = 0.5000000000;

	static unsigned NUM_THREADS = 5;


	static inline const double& max(const double& a, const double& b) { return a > b ? a : b; };
	static inline double abs(const double& a) { return a > ZERO ? a : -a; };

	static inline bool areEqual(const double& a, const double& b)
	{
		const double m = max(abs(a), abs(b));
		return m < DIF_TOLERANCE ? true : (abs(a - b) / m) < DIF_TOLERANCE;
	}

	static inline bool isZero(const double& a)
	{
		return areEqual(a, ZERO);
	}

	static inline double sgnOf(const double& a)
	{
		return a < 0 ? -ONE : ONE;
	}
}