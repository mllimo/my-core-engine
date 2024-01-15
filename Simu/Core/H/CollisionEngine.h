#pragma once

#include <CoreAPI.h>

#include <deque>
#include <memory>

#include <Core/H/Object.h>

namespace core {
	class CORE_EXPORT CollisionEngine {
	public:

		static void Add(Object* object);
		static void Update();

	private:
		static std::deque<Object*> _objects;
	};
}
