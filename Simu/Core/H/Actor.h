#pragma once


#include <memory>
#include <vector>
#include <string_view>

#include <raylib.h>

#include <CoreAPI.h>
#include <Core/H/Collider.h>

namespace core {

	class CORE_EXPORT Actor {
	public:
		struct Properties {
			float rotation = 0;
			Vector2 position = { 0, 0 };
			Collider collider;
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
		void SetProperties(Properties properties);
		void SetCollider(Collider collider);
		void SetPosition(Vector2 position);
		void SetRotation(float rotation);
		void SetTag(const std::string& tag);


		// Base Getters
		const Properties& GetProperties() const { return _properties; }
		const Collider& GetCollider() const { return _properties.collider; }
		Vector2 GetPosition() { return _properties.position; }
		float GetRotation() { return _properties.rotation; }
		std::string_view GetTag() { return _properties.tag; }

		// Custom functions
		virtual void UpdateLogic() {}
		virtual void UpdateDraw() {}
		virtual void OnCollision(Actor*) {}
		virtual void OnNoCollision() {}

		// Debug drawss
		void DebugDrawDirectionLine();

	protected:
		// Custom Setters
		virtual	void SetPropertiesImp(Properties /*properties*/) {}
		virtual void SetPositionImp(Vector2 /*position*/ ) {}
		virtual void SetRotationImp(float /*rotation*/) {}

	private:
		Properties _properties;
		bool _enable_collider = false;
	};
}
