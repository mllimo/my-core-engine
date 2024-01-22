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

}
