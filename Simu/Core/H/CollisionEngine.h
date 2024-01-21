#pragma once

#include <CoreAPI.h>

#include <deque>
#include <memory>

#include <Core/H/Actor.h>

namespace core {
	class CORE_EXPORT CollisionEngine {
	public:

		static void Add(Actor* object);
		static void Remove(Actor* object);
		static void Update();

	private:
		static std::deque<Actor*> _objects;
	};
}
