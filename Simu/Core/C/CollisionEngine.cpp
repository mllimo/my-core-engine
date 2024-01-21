#include <Core/H/CollisionEngine.h>

#include <unordered_set>

namespace core {

	std::deque<Actor*> CollisionEngine::_objects = {};

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

	void CollisionEngine::Update()
	{
		for (auto it = _objects.begin(); it != _objects.end(); ++it) {
			for (auto jt = std::next(it); jt != _objects.end(); ++jt) {
				auto collider_i = (*it)->GetCollider();
				auto collider_j = (*jt)->GetCollider();

				if (collider_i.IsColliding(collider_j)) {
					(*it)->OnCollision(*jt);
					(*jt)->OnCollision(*it);
				}

			}
		}
	}
}
