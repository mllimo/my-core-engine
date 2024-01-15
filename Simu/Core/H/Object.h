#pragma once

#include <CoreAPI.h>

#include <memory>

#include <raylib.h>

namespace core {
	class Object : public std::enable_shared_from_this<Object> {
	public:
		struct Properties {
			Vector2 position;
			Vector2 collider;
		};

		Object() = default;
		Object(const Object&) = default;
		Object(Object&&) = default;

		Object(Vector2 position);

		Object& operator=(const Object&) = default;
		Object& operator=(Object&&) = default;

		const Properties& GetProperties() const { return _properties; }
		Properties& GetProperties() { return _properties; }

		void EnableToCollide();
		void SetCollider(Vector2 collider);

		virtual void UpdateLogic() {}
		virtual void UpdateDraw() {}
		virtual void OnCollision(Object* other) {}

	protected:
		Properties _properties;
	};
}
