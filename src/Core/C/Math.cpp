#include <Core/H/Math.h>

namespace core {
	Vector2 RotatePoint(Vector2 pivot, Vector2 point, float radians)
	{
		float sin_a = sin(radians);
		float cos_a = cos(radians);

		float pivotX = pivot.x;
		float pivotY = pivot.y;

		float x = point.x - pivotX;
		float y = point.y - pivotY;

		// Aplicar la rotación
		point.x = cos_a * x - sin_a * y + pivotX;
		point.y = sin_a * x + cos_a * y + pivotY;

		return point;
	}

	float DistanceSquared(const Vector2& a, const Vector2& b)
	{
		float dx = b.x - a.x;
		float dy = b.y - a.y;
		return (dx * dx + dy * dy);
	}

	Vector2 ToRayVetor2(const b2Vec2& a)
	{
		return { a.x, a.y };
	}

	b2Vec2 ToB2Vetor2(const Vector2& a)
	{
		return { a.x, a.y };
	}

	b2Vec2 Scale(const Vector2& a)
	{
		return b2Vec2(a.x * SCALE_FACTOR, a.y * SCALE_FACTOR);
	}

	Vector2 Scale(const b2Vec2& a)
	{
		return Vector2(a.x / SCALE_FACTOR, a.y / SCALE_FACTOR);
	}
}
