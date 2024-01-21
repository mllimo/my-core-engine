#include <Core/H/Actor.h>

#include <raymath.h>

#include <Core/H/CollisionEngine.h>

namespace core {

	Actor::Actor(Vector2 position)
	{
		_properties.position = position;
	}

	Actor::~Actor()
	{
		_enable_collider = false;
		CollisionEngine::Remove(this);
	}

	void Actor::EnableCollider()
	{
		_enable_collider = true;
		CollisionEngine::Add(this);
	}

	void Actor::DisableCollider()
	{
		_enable_collider = false;
		CollisionEngine::Remove(this);
	}

	void Actor::SetProperties(Properties properties)
	{
		_properties = properties;
		SetPropertiesImp(properties);
	}

	void Actor::SetCollider(Collider collider)
	{
		_properties.collider = collider;
	}

	void Actor::SetPosition(Vector2 position)
	{
		_properties.position = position;

		if (_properties.collider._geometry)
			_properties.collider._geometry->SetPosition(position);

		SetPositionImp(position);
	}

	void Actor::SetRotation(float rotation)
	{
		_properties.rotation = rotation;

		if (_properties.collider._geometry)
			_properties.collider._geometry->SetRotation(rotation);

		SetRotationImp(rotation);
	}

	void Actor::SetTag(const std::string& tag)
	{
		_properties.tag = tag;
	}

	void Actor::DebugDrawDirectionLine()
	{
		Vector2 center = GetPosition();
		Vector2 direction = { cos(GetRotation()) * 100, sin(GetRotation()) * 100 };
		DrawLineEx(center, Vector2Add(center, direction), 2, GREEN);
	}


}
 