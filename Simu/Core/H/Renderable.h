#pragma once

#include <raylib.h>

#include <CoreAPI.h>
#include <Core/H/Geometry.h>

namespace core {
	class CORE_EXPORT Renderable {
	public:
		// Reference to the render geometry
		Renderable(Geometry* geometry);
		virtual ~Renderable();


		// Getters
		Color GetColor() const { return _color; }
		const Geometry* GetGeometry() const { return _geometry; }
		const Texture& GetTexture() const { return _texture; }


		// Setters
		void SetColor(Color);
		void SetTexture(Texture);
		void SetTexture(Image&&); //< Renderable will be the next owner


		// Custom methods
		virtual void Draw();

	protected:
		Geometry* _geometry = nullptr;
		Color _color;
		Image _image;
		Texture2D _texture;
	};
}
