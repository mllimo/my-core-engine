#pragma once

#include <CoreAPI.h>

#include <raymath.h>

#include <vector>

namespace core {
	
	class CORE_EXPORT Geometry {
	public:
		Geometry() = default;
		Geometry(const Geometry&) = default;
		Geometry(Geometry&&) = default;

		Geometry& operator=(const Geometry&) = default;
		Geometry& operator=(Geometry&&) = default;

		virtual Geometry* Copy() const;

		// Base Setters
		void SetPosition(Vector2 position);
		void SetRotation(float radians);
		void SetOrigin(Vector2 origin);

		// Base Getters
		Vector2 GetPosition() const { return (_vertices.empty() ? Vector2Zero() : _vertices.front()); }
		float   GetRotation() const { return _angle; }
		Vector2 GetOrigin() const { return _origin; }
		Vector2 GetCenter() const;

		// Implementations
		virtual const std::vector<Vector2>& GetVertices() { return _vertices; }

	protected:
		const Vector2& At(size_t index) const { return _vertices[index]; }
		Vector2& At(size_t index) { return _vertices[index]; }

		void ResizeVertices(size_t size);
	
	private:
		float _angle = 0;
		Vector2 _origin = { 0, 0 };
		std::vector<Vector2> _vertices;

	};

	class CORE_EXPORT Square : public Geometry {
	public:
		using Geometry::Geometry;

		Square(Vector2 position, Vector2 size);

		Geometry* Copy() const override;
		
		// Setters
		void SetSize(Vector2 size);


		// Getters
		Vector2 GetSize() const;

	private:
		Vector2 _size;
	};
}
