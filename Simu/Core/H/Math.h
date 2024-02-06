#pragma once

#include <CoreAPI.h>

#include <cmath>

#include <raymath.h>

#include <box2d/box2d.h>

namespace core {
	inline float SCALE_FACTOR = 0.1f; //< box2d does not work with pixels magnitudes
	CORE_EXPORT Vector2 RotatePoint(Vector2 pivot, Vector2 point, float radians);
	CORE_EXPORT float DistanceSquared(const Vector2& a, const Vector2& b);
	CORE_EXPORT Vector2 ToRayVetor2(const b2Vec2& a);
	CORE_EXPORT b2Vec2 ToB2Vetor2(const Vector2& a);
	CORE_EXPORT b2Vec2 Scale(const Vector2& a);
	CORE_EXPORT Vector2 Scale(const b2Vec2& a);
}
