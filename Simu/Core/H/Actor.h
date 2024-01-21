#pragma once


#include <memory>
#include <vector>

#include <raylib.h>

#include <CoreAPI.h>
#include <Core/H/Geometry.h>

namespace core {

	class Collider {
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

	class Actor {
	public:
		struct Properties {
			float rotation = 0;
			Vector2 position = { 0, 0 };
			Collider collider;
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
		void SetProperties(Properties properties);
		void SetCollider(Collider collider);
		void SetPosition(Vector2 position);
		void SetRotation(float rotation);

		
		// Base Getters
		const Properties& GetProperties() const { return _properties; }
		const Collider& GetCollider() const { return _properties.collider; }
		Vector2 GetPosition() { return _properties.position; }
		float GetRotation() { return _properties.rotation; }


		// Custom functions
		virtual void UpdateLogic() {}
		virtual void UpdateDraw() {}
		virtual void OnCollision(Actor*) {}

	protected:
		// Custom Setters
		virtual	void SetPropertiesImp(Properties /*properties*/) {}
		virtual void SetPositionImp(Vector2 /*position*/ ) {}
		virtual void SetRotationImp(float /*rotation*/) {}

		Properties _properties;
		bool _enable_collider = false;
	};
}
