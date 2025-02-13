#pragma once
#include "constants.hpp"
#include "types.hpp"



namespace utils {

	namespace dim_1d {

		// ѕроверка, находитс€ ли значение в пределах границ [0, size)
		inline bool isInBorder(const int value, const int size) noexcept {
			return value >= 0 && value < size;
		}

		// ѕроверка, находитс€ ли значение в пределах границ [lower_bound, upper_bound)
		inline bool isInBorder(const int value, const int lower_bound, const int upper_bound) noexcept {
			return value >= lower_bound && value < upper_bound;
		}

	}

	namespace dim_2d {

	}

	namespace dim_3d {

	}

	namespace dim_4d {

	}

}