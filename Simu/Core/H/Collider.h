#pragma once

#include <memory>

#include <raylib.h>
#include <raymath.h>

#include <CoreAPI.h>
#include <Core/H/Geometry.h>

namespace core {
	class CORE_EXPORT Collider {
		friend class Actor;

	public:
		Collider() = default;
		Collider(const Collider& other);
		Collider(Collider&&) = default;

		Collider& operator=(const Collider&);
		Collider& operator=(Collider&&) = default;

		void SetGeometry(std::unique_ptr<Geometry> collider) { _geometry = std::move(collider); }

		virtual bool IsColliding(Collider& other) const;

	protected:
		std::unique_ptr<Geometry> _geometry;
	};
}
