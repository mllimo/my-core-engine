#pragma once

#include <chrono>

#include <CoreAPI.h>

namespace core {
	class CORE_EXPORT DeltaTime {
	public:
		DeltaTime();
		~DeltaTime();

		static float delta;

	private:
		std::chrono::steady_clock::time_point _start;
	};
}
