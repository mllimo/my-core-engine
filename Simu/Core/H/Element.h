#pragma once

#include <CoreAPI.h>

#include <utility>
#include <string_view>

#include <raylib.h>

namespace core {
	class CORE_EXPORT Element {
	public:
		struct Properties {
			Vector2 force;
			Vector2 position;
			Vector2 size;
			float density; // kg/m³
			float temperature; // in celsius
			float thermal_conductivity; //  k = (W/m⋅°C)

			Properties operator*(float scalar);
		};

		Vector2 GetPosition() const { return _properties.position; }
		Vector2 GetSize() const { return _properties.size; }
		std::string_view GetName() const { return _name; }
		Color GetColor() const { return _color; }
		const Properties& GetProperties() const { return _properties; }
		Properties& GetProperties() { return _properties; }

		void SetPosition(Vector2 pos)  { _properties.position = pos; }
		void SetSize(Vector2 size) { _properties.size = size; }
		void SetColor(Color color) { _color = color; }

		virtual Properties InteractWith(const Element& other);
		virtual Element* ReactWith(const Element& other) { return nullptr; }

	protected:
		std::string _name;
		Properties _properties;
		Color _color;
	};
}
