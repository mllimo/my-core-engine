#pragma once

#include <memory>

#include <raylib.h>
#include <raymath.h>

#include <CoreAPI.h>
#include <Core/H/Geometry.h>

namespace core {
	class CORE_EXPORT Collider {
		friend class CollisionEngine;
		friend class Actor;
	public:
		Collider() = default;
		Collider(const Collider& other);
		Collider(Collider&&) = default;

		Collider(const Geometry& collider) { _geometry.reset(collider.Copy()); }
		Collider(std::unique_ptr<Geometry> collider) { _geometry = std::move(collider); }

		Collider& operator=(const Collider&);
		Collider& operator=(Collider&&) = default;

		void SetGeometry(const Geometry& collider) { _geometry.reset(collider.Copy()); }
		void SetGeometry(std::unique_ptr<Geometry> collider) { _geometry = std::move(collider); }

		const Geometry& GetGeometry() const { return *_geometry; }

		virtual bool IsColliding(Collider& other) const;

	protected:
		std::unique_ptr<Geometry> _geometry;

	private:
		bool IsCollidingVsCircle(const Geometry& this_geo, const Circle& other) const;
		bool IsCollidingCircleVsCircle(const Circle& this_circle, const Circle& other) const;
	};
}
