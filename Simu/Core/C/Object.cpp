#include <Core/H/Object.h>

#include <Core/H/CollisionEngine.h>

namespace core {
	Object::Object(Vector2 position)
	{
		_properties.position = position;
	}

	void Object::EnableToCollide()
	{
		CollisionEngine::Add(this);
	}

	void Object::SetCollider(Vector2 collider)
	{
		_properties.collider = collider;
	}
}
