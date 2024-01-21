#include <Core/H/CollisionEngine.h>

#include <unordered_set>

namespace core {

	std::deque<Actor*> CollisionEngine::_objects = {};
	std::unordered_map<Actor*, std::unordered_set<Actor*>> CollisionEngine::_collision_map = {};

	void CollisionEngine::Add(Actor* object)
	{
		_objects.emplace_back(object);
	}

	void CollisionEngine::Remove(Actor* object)
	{
		auto found_it = std::find(_objects.begin(), _objects.end(), object);
		if (found_it == _objects.end()) return;
		_objects.erase(found_it);
	}

	bool CollisionEngine::AreColliding(Actor* a, Actor* b)
	{
		auto exist_a = _collision_map.find(a);
		if (exist_a == _collision_map.end()) return false;
		auto collide_with_b = _collision_map.find(b);
		return collide_with_b != _collision_map.end();
	}

	bool CollisionEngine::AreColliding(Actor* a, std::string_view tag)
	{
		auto exist_a = _collision_map.find(a);
		if (exist_a == _collision_map.end()) return false;

		for (const auto& actor : exist_a->second) {
			if (actor->GetTag() == tag) return true;
		}

		return false;
	}

	void CollisionEngine::Update()
	{
		_collision_map.clear();
		for (auto it = _objects.begin(); it != _objects.end(); ++it) {
			for (auto jt = std::next(it); jt != _objects.end(); ++jt) {
				auto collider_i = (*it)->GetCollider();
				auto collider_j = (*jt)->GetCollider();

				if (collider_i.IsColliding(collider_j)) {
					(*it)->OnCollision(*jt);
					(*jt)->OnCollision(*it);
					_collision_map[*it].insert(*jt);
					_collision_map[*jt].insert(*it);
				}

			}
		}
	}
}
