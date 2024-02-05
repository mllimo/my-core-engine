#include <Core/H/Geometry.h>

namespace core {

	Geometry* Geometry::Copy() const
	{
		return new Geometry(*this);
	}

	b2Shape* Geometry::ConstructB2FromThis() const
	{
		Vector2 center = GetCenter();

		b2PolygonShape* shape = new b2PolygonShape;

		// b2 vertices are relative to the body centroid
		b2Vec2 vertices[8];
		for (int i = 0; i < (int)_vertices.size(); ++i) {
			vertices[i] = Scale(Vector2Subtract(_vertices[i], center));
		}

		shape->Set(vertices, (int)_vertices.size());

		return shape;
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

		float pivotX = _origin.x;
		float pivotY = _origin.y;

		for (auto& vertex : _vertices) {
			float x = vertex.x - pivotX;
			float y = vertex.y - pivotY;

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
		Updateb2();
	}

	void Geometry::Updateb2()
	{
		if (_b2_shape) {
			//for (int i = 0; i < _vertices.size(); ++i) {
			//	_b2_shape->m_vertices[i] = Scale(_vertices[i]);
			//}
			//_b2_shape->m_count = (int32_t)_vertices.size();
		}
	}

	void Geometry::UpdateFromb2()
	{
		//for (int i = 0; i < _b2_shape->m_count; ++i) {
		//	_vertices[i] = Vector2Add(Scale(_b2_shape->m_vertices[i]));
		//}
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
		At(3) = { At(0).x + size.x, At(0).y };
		SetRotation(GetRotation());

		Updateb2();
	}

	Vector2 Square::GetSize() const
	{
		return _size;
	}

	//------------------------------------------------------------------------------------
	// Circle
	//------------------------------------------------------------------------------------

	Circle::Circle(Vector2 position, float radius)
	{
		ResizeVertices(1);
		At(0) = position;
		SetOrigin(position);
		SetRadius(radius);
	}

	Geometry* Circle::Copy() const
	{
		return new Circle(*this);
	}

	void Circle::SetRadius(float radius)
	{
		_radius = radius;
	}

	float Circle::GetRadius() const
	{
		return _radius;
	}

}
