#pragma once

#include <CoreAPI.h>

#include <cmath>

#include <raymath.h>

namespace core {
	CORE_EXPORT Vector2 RotatePoint(Vector2 pivot, Vector2 point, float radians);
	CORE_EXPORT float DistanceSquared(const Vector2& a, const Vector2& b);
}
