#pragma once


#include <vector>

#include <raymath.h>

#include <box2d/box2d.h>

#include <CoreAPI.h>
#include <Core/H/Math.h>

namespace core {

	//TODO: Fix _origin
	class CORE_EXPORT Geometry {
		friend class CollisionEngine;
	public:
		enum class Kind{
			POLY,
			SQUARE,
			TRIANGLE,
			CIRCLE
		};

		Geometry(Kind kind);
		Geometry(const Geometry&) = default;
		Geometry(Geometry&&) = default;

		virtual ~Geometry() = default;

		Geometry& operator=(const Geometry&) = default;
		Geometry& operator=(Geometry&&) = default;

		// User will be the owner of the pointer
		virtual Geometry* Copy() const;

		// User will be the owner of the pointer
		virtual b2Shape* ConstructB2FromThis() const;

		// Base Setters
		void SetPosition(Vector2 position);
		void SetRotation(float radians);

		// Set a relative position from the first vertex to be the new origin
		void SetOrigin(Vector2 origin); //< TODO: Fix

		// Base Getters
		Vector2 GetPosition() const { return (_vertices.empty() ? Vector2Zero() : _vertices.front()); }
		const Vector2& At(size_t index) const { return _vertices[index]; }
		float   GetRotation() const { return _angle; }
		Vector2 GetOrigin() const { return _origin; }
		Vector2 GetCenter() const;
		Kind GetKind() const { return _kind; }


		// Implementations
		virtual const std::vector<Vector2>& GetVertices() const { return _vertices; }

	protected:
		Vector2& At(size_t index) { return _vertices[index]; }

		void ResizeVertices(size_t size);

	private:
		Kind _kind;
		float _angle = 0;
		Vector2 _origin = { 0, 0 }; // Relative to position
		std::vector<Vector2> _vertices;
	};

//===========================================================

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

//===========================================================

	class CORE_EXPORT Circle : public Geometry {
	public:
		using Geometry::Geometry;

		Circle(Vector2 position, float radius);

		Geometry* Copy() const override;
		b2Shape* ConstructB2FromThis() const override;

		// Setters
		void SetRadius(float radius);


		// Getters
		float GetRadius() const;

	private:
		float _radius;
	};

//===========================================================

	class CORE_EXPORT Triangle : public Geometry {
	public:
		using Geometry::Geometry;

		// p1: left, p2: upper-middle, p3: right 
		Triangle(Vector2 p1, Vector2 p2, Vector2 p3);

		Geometry* Copy() const override;

		// Setters
		void SetVertices(Vector2 p1, Vector2 p2, Vector2 p3);


		// Getters
		Vector2 GetP1() const { return At(0); }
		Vector2 GetP2() const { return At(1); }
		Vector2 GetP3() const { return At(2); }
	};
}
