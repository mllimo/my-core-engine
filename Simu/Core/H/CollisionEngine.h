#pragma once

#include <CoreAPI.h>

#include <deque>
#include <memory>
#include <unordered_set>
#include <unordered_map>

#include <box2d/box2d.h>

#include <Core/H/Actor.h>
#include <Core/H/Singleton.h>


namespace core {
	class CORE_EXPORT CollisionEngine : public Singleton<CollisionEngine> {
		friend class Listener;
	public:
		CollisionEngine() : _world({0, 0}) { }

		void Init() override;
		void Add(Actor* object);
		void Remove(Actor* object);
		bool AreColliding(Actor* a, Actor* b);
		bool AreColliding(Actor* a, std::string_view tag);
		void Update();

	private:
		b2World _world;
		std::deque<Actor*> _objects;
		std::unordered_map<Actor*, std::unordered_set<Actor*>> _collision_map;
	};
}
