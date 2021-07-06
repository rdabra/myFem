#pragma once

namespace putils
{
	static double DIF_TOLERANCE = 0.0000001;

	static double ZERO = 0.0;

	static inline const double& max(const double& a, const double& b) { return a > b ? a : b; };
	static inline const double abs(const double& a) { return a > 0.0 ? a : -a; };

	static bool areEqual(const double& a, const double& b) {
		double m = max(abs(a), abs(b));
		return  (m == 0.0 ? 0.0 : abs(a - b) / m) < DIF_TOLERANCE;
	}
}