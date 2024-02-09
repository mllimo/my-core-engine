#include <Core/H/DeltaTime.h>

namespace core {
	float DeltaTime::delta = 0.0000001f;

	DeltaTime::DeltaTime()
	{
		_start = std::chrono::high_resolution_clock::now();
	}

	DeltaTime::~DeltaTime()
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - _start).count();
		core::DeltaTime::delta = 1 / (diff == 0 ? 0.000000000000001f : diff);
	}
}
