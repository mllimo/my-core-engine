#pragma once

#include <raymath.h>

#include <CoreAPI.h>

namespace core {

	class Collider;

	class Rigid {
	public:
		Rigid(const Rigid&) = default;
		Rigid(Rigid&&) = default;

		Rigid(const Collider* collider = nullptr) : _force({0, 0}), _collider(collider) {}

		Rigid& operator=(const Rigid&) = default;
		Rigid& operator=(Rigid&&) = default;

		void SetForce(Vector2 force) { _force = force; }
		Vector2 GetForce() const { return _force; }

		void SetStatic(bool is_static) { _is_static = is_static; }
		bool GetStatic(bool is_static) const { return _is_static; }

	private:
		Vector2 _force;
		const Collider* _collider;
		bool _is_static = false;
	};
}
