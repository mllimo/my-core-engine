#include <Core/H/Actor.h>

#include <raymath.h>

#include <Core/H/CollisionEngine.h>

namespace core {

	Collider::Collider(const Collider& other)
	{
		_geometry.reset(other._geometry->Copy());
	}

	Collider& Collider::operator=(const Collider& other)
	{
		_geometry.reset(other._geometry->Copy());
		return *this;
	}

	bool Collider::IsColliding(Collider& other) const
	{
		auto& vertices = _geometry->GetVertices();
		auto& other_vertices = other._geometry->GetVertices();

		if (vertices.size() == 0 || other_vertices.size() == 0) return false;
		
		auto& bigger_vertices_vector = (vertices.size() >= other_vertices.size()
			? vertices
			: other_vertices
		);

		auto& lower_vertices_vector = (other_vertices.size() <= vertices.size()
			? other_vertices
			: vertices
		);

		for (const auto& vertex : lower_vertices_vector) {
			if (CheckCollisionPointPoly(vertex, (Vector2*)bigger_vertices_vector.data(), bigger_vertices_vector.size()))
				return true;
		}

		// When vertices are not in the area of the poly
		for (long i = (long)bigger_vertices_vector.size() - 1; i >= 0; i -= 1) {
			if (i - 1 < 0) break;
			Vector2 i_A = bigger_vertices_vector[i];
			Vector2 i_B = bigger_vertices_vector[i - 1ll];

			for (long j = (long)lower_vertices_vector.size() - 1; j >= 0; j -= 1) {
				if (j - 1 < 0) break;
				Vector2 j_A = lower_vertices_vector[j];
				Vector2 j_B = lower_vertices_vector[j - 1ll];

				Vector2 dummy;
				if (CheckCollisionLines(i_A, i_B, j_A, j_B, &dummy))
					return true;
			}
		}

		return false;
	}


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
}
 