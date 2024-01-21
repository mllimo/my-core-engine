#include <Core/H/Geometry.h>

namespace core {

	Geometry* Geometry::Copy() const
	{
		return new Geometry(*this);
	}

	Vector2 Geometry::GetCenter() const
	{
		float x = 0;
		float y = 0;

		for (auto vertex : _vertices) {
			x += vertex.x;
			y += vertex.y;
		}

		return { x / _vertices.size(), y / _vertices.size() };
	}


	void Geometry::SetPosition(Vector2 position)
	{
		Vector2 distance = Vector2Subtract(position, _origin);
		_origin = Vector2Add(_origin, distance);

		for (auto& vertex : _vertices) {
			vertex = Vector2Add(vertex, distance);
		}
	}

	void Geometry::SetRotation(float radians)
	{
		float sin_a = sin(radians - _angle);
		float cos_a = cos(radians - _angle);

		// Obtener el vértice alrededor del cual se va a rotar (en este caso, el vértice en el índice 0)
		float pivotX = _origin.x;
		float pivotY = _origin.y;

		for (auto& vertex : _vertices) {
			float x = vertex.x - pivotX;
			float y = vertex.y - pivotY;

			// Aplicar la rotación
			vertex.x = cos_a * x - sin_a * y + pivotX;
			vertex.y = sin_a * x + cos_a * y + pivotY;
		}
		_angle = radians;
	}

	void Geometry::SetOrigin(Vector2 origin)
	{
		_origin = origin;
	}

	void Geometry::ResizeVertices(size_t size)
	{
		_vertices.resize(size);
	}

	//------------------------------------------------------------------------------------
	// Square
	//------------------------------------------------------------------------------------
	Square::Square(Vector2 position, Vector2 size) :
		_size(size)
	{
		ResizeVertices(4);
		At(0) = position;
		SetOrigin(position);
		SetSize(size);
	}

	Geometry* Square::Copy() const
	{
		return new Square(*this);
	}

	void Square::SetSize(Vector2 size)
	{
		_size = size;
		ResizeVertices(4);

		At(1) = { At(0).x, At(0).y + size.y };
		At(2) = { At(0).x + size.x, At(0).y + size.y };
		At(3) = { At(0).x + size.x, At(0).y};
		SetRotation(GetRotation());
	}

	Vector2 Square::GetSize() const
	{
		return _size;
	}
}
