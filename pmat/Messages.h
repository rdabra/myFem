#pragma once

namespace messages {
	constexpr const char* OPERANDS_EQUAL{ "Operands must have same size" };
	constexpr const char* INDEX_OUT{ "Index out of bounds" };
	constexpr const char* OPERANDS_MAT_PROD{ "Sizes of left column and right row must be equal" };
	constexpr const char* NONCOMPT_RESP{ "Response object size is not compatible" };
	constexpr const char* NONCOMPT_ARG{ "Argument is not compatible" };

	constexpr const char* MATRIX_SINGULAR{ "Matrix is singular" };
	constexpr const char* ELEM_SWAPPED{ "Elements cannot be swapped" };


}