#include <Core/H/CollisionEngine.h>

#include <unordered_set>

namespace core {

	std::deque<Object*> CollisionEngine::_objects = {};

	void CollisionEngine::Add(Object* object)
	{
		_objects.emplace_back(object);
	}

	static Rectangle ConstructRect(const Object& object)
	{
		Rectangle rect;
		rect.x = object.GetProperties().position.x;
		rect.y = object.GetProperties().position.y;
		rect.width = object.GetProperties().collider.x;
		rect.height = object.GetProperties().collider.y;
		return rect;
	}

	void CollisionEngine::Update()
	{
		for (auto it = _objects.begin(); it != _objects.end(); ++it) {
			for (auto jt = std::next(it); jt != _objects.end(); ++jt) {				
				Rectangle irec = ConstructRect(*(*it));
				Rectangle jrec = ConstructRect(*(*jt));
				if (CheckCollisionRecs(irec, jrec)) {
					(*it)->OnCollision(*jt);
					(*jt)->OnCollision(*it);
				}
			}
		}
	}
}
