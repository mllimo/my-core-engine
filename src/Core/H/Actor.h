#pragma once

#include <memory>
#include <vector>
#include <string_view>

#include <raylib.h>

#include <box2d/box2d.h>

#include <CoreAPI.h>
#include <Core/H/Collider.h>

namespace core {
	class CORE_EXPORT Actor {
		friend class CollisionEngine;
	public:
		struct Properties {
			struct B2Properties {
				b2Body* body = nullptr;
				b2Fixture* fixture = nullptr;
			};

			float rotation = 0;
			Vector2 position = { 0, 0 };
			Collider collider;
			B2Properties b2_properties;
			std::string tag;
		};

		Actor() = default;
		Actor(const Actor&) = default;
		Actor(Actor&&) = default;
		Actor(Vector2 position);

		virtual ~Actor();

		Actor& operator=(const Actor&) = default;
		Actor& operator=(Actor&&) = default;

		void EnableCollider();
		void DisableCollider();

		// Base Setters
		void SetProperties(Properties&& properties);
		void SetCollider(Collider collider);
		void SetPosition(Vector2 position);
		void SetRotation(float rotation);
		void SetTag(const std::string& tag);

		// Base Getters
		const Properties& GetProperties() const { return _properties; }
		const Collider& GetCollider() const { return _properties.collider; }
		Collider& GetCollider() { return _properties.collider; }
		Vector2 GetPosition() { return _properties.position; }
		float GetRotation() { return _properties.rotation; }
		std::string_view GetTag() { return _properties.tag; }

		// Custom functions
		virtual void UpdateLogic() {}
		virtual void UpdateDraw() {}
		virtual void OnNoCollision() {}

		// Debug draws
		void DebugDrawDirectionLine();

	protected:
		// Custom Setters
		virtual	void SetPropertiesImp(const Properties& /*properties*/) {}
		virtual void SetPositionImp(Vector2 /*position*/) {}
		virtual void SetRotationImp(float /*rotation*/) {}

		// UpdatesFromB2
		void UpdateFromB2();

		Properties _properties;
		bool _enable_collider = false;
		bool _enable_physics = false;
	};
}
