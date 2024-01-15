#include <Core/H/Element.h>

#include <raymath.h>

namespace core {

	Element::Properties Element::Properties::operator*(float scalar)
	{
		Properties result;
		result.force = Vector2Scale(force, scalar);
		return result;
	}

	Element::Properties Element::InteractWith(const Element& other)
	{
		Properties result = _properties;

		result.force = Vector2Add(other._properties.force, result.force);
		result.position = Vector2Add(other._properties.position, result.force);

		bool is_hotter = _properties.temperature > other._properties.temperature;
		float hotter = std::max(_properties.temperature, other._properties.temperature);
		float cooler = std::min(_properties.temperature, other._properties.temperature);

		float jul = _properties.thermal_conductivity * (hotter - cooler);
		float temperature = jul * 0.0005266;
		result.temperature = (is_hotter ? result.temperature - temperature : result.temperature + temperature);

		return result;
	}
}
