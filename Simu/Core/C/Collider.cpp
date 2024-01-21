#include <Core/H/Collider.h>

#include <vector>

namespace core {
	static bool CheckCollisionPointPoly(Vector2 point, Vector2* points, int pointCount)
	{
		bool inside = false;

		if (pointCount > 2)
		{
			for (int i = 0, j = pointCount - 1; i < pointCount; j = i++)
			{
				if ((points[i].y > point.y) != (points[j].y > point.y) &&
					(point.x < (points[j].x - points[i].x) * (point.y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
				{
					inside = !inside;
				}
			}
		}

		return inside;
	}

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
			if (core::CheckCollisionPointPoly(vertex, (Vector2*)bigger_vertices_vector.data(), bigger_vertices_vector.size()))
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
}
