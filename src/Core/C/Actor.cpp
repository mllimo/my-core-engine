#include <sstream>

#include <Core/H/Actor.h>

#include <raymath.h>

#include <Core/H/CollisionEngine.h>

namespace core {

	Actor::Actor(Vector2 position)
	{
		SetPosition(position);
	}

	Actor::~Actor()
	{
		DisableCollider();
	}

	void Actor::EnableCollider()
	{
		CollisionEngine::Instance().Add(this);
		_enable_collider = true;
	}

	void Actor::DisableCollider()
	{
		if (_enable_collider) {
			CollisionEngine::Instance().Remove(this);
			_enable_collider = false;
		}
	}

	void Actor::SetProperties(Properties&& properties)
	{
		_properties = std::move(properties);
		SetPropertiesImp(_properties);
	}

	void Actor::SetCollider(Collider collider)
	{
		_properties.collider = std::move(collider);
	}

	void Actor::SetPosition(Vector2 position)
	{
		_properties.position = position;

		if (_properties.collider._geometry)
			_properties.collider._geometry->SetPosition(position);

		if (_properties.b2_properties.body) {
			auto center = Scale(_properties.collider._geometry->GetCenter());
			_properties.b2_properties.body->SetTransform(center, GetRotation());
		}

		SetPositionImp(position);
	}

	void Actor::SetRotation(float rotation)
	{
		_properties.rotation = rotation;

		if (_properties.b2_properties.body)
			_properties.b2_properties.body->SetTransform(Scale(GetPosition()), GetRotation());

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
		// TODO: Improve all transoform system
		float angle = _properties.b2_properties.body->GetAngle();
		_properties.rotation = angle;
		_properties.collider._geometry->SetRotation(angle);
		SetRotationImp(angle);

		auto b2_center_scale = Scale(_properties.b2_properties.body->GetWorldCenter());
		auto previus_origin = _properties.collider.GetGeometry().GetOrigin();

		auto temp_origin = Vector2Subtract(_properties.collider.GetGeometry().GetCenter(), _properties.collider.GetGeometry().GetPosition());
		_properties.collider.GetGeometry().SetOrigin(temp_origin);
		_properties.collider.GetGeometry().SetPosition(b2_center_scale);
		_properties.collider.GetGeometry().SetOrigin(previus_origin);

		_properties.position = _properties.collider.GetGeometry().GetPosition();
		_properties.collider._geometry->SetPosition(_properties.position);
		SetPositionImp(_properties.position);
	}

}
