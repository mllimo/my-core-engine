#pragma once

#include <CoreAPI.h>

namespace core {
	class CORE_EXPORT DeltaTime {
	public:
		DeltaTime() = delete;
		static float delta;
	};
}
