#pragma once

#include <CoreAPI.h>

#include <deque>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include <box2d/box2d.h>

#include <Core/H/Actor.h>

namespace core {
	class CORE_EXPORT CollisionEngine {
	public:
		static void Init();
		static void Add(Actor* object);
		static void Remove(Actor* object);
		static bool AreColliding(Actor* a, Actor* b);
		static bool AreColliding(Actor* a, std::string_view tag);
		static void Update();

	private:
		static b2World _world;
		static std::deque<Actor*> _objects;
		static std::unordered_map<Actor*, std::unordered_set<Actor*>> _collision_map;
	};
}
