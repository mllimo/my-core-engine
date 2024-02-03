#include <sstream>

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

	void Actor::SetProperties(Properties&& properties)
	{
		_properties = std::move(properties);
		SetPropertiesImp(_properties);
	}

	void Actor::SetCollider(Collider collider)
	{
		_properties.collider = collider;
	}

	void Actor::SetPosition(Vector2 position)
	{
		_properties.position = position;

		if (_properties.b2_properties.body)
			_properties.b2_properties.body->SetTransform(ToB2Vetor2(position), GetRotation());

		if (_properties.collider._geometry)
			_properties.collider._geometry->SetPosition(position);

		SetPositionImp(position);
	}

	void Actor::SetRotation(float rotation)
	{
		_properties.rotation = rotation;

		if (_properties.b2_properties.body)
			_properties.b2_properties.body->SetTransform(ToB2Vetor2(GetPosition()), GetRotation());

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

	void Actor::UpdateFromB2()
	{
		b2Vec2 position = _properties.b2_properties.body->GetPosition();
		float anglee = _properties.b2_properties.body->GetAngle();

		std::stringstream ss;
		ss << "ori -> " << GetPosition().x << "|" << GetPosition().y << " | angle: " << anglee << '\n';
		ss << "bo2 -> " << position.x << "|" << position.y << " | angle: " << anglee;

		TraceLog(LOG_INFO, ss.str().c_str());

		float angle = _properties.b2_properties.body->GetAngle();
		SetPosition(ToRayVetor2(_properties.b2_properties.body->GetPosition()));
		SetRotation(angle);
	}

}
 