#include <functional>

#include <Core/H/Renderable.h>
#include <Core/H/Exceptions.h>

#include <rlgl.h>

namespace core {
	Renderable::Renderable(Geometry* geometry) : _image({ 0 })
	{
		if (geometry == nullptr)
			throw RenderableException("Bad geometry ptr");

		_geometry = geometry;
	}

	Renderable::~Renderable()
	{
		if (_image.data != nullptr) {
			UnloadImage(_image);	 // from CPU
			UnloadTexture(_texture); // from GPU
		}
	}


	void Renderable::SetColor(Color color)
	{
		_color = color;
	}

	void Renderable::SetTexture(Texture texture)
	{
		_image = LoadImageFromTexture(texture);
		_texture = std::move(texture);
	}

	void Renderable::SetTexture(Image&& image)
	{
		_image = std::move(image);
		_texture = LoadTextureFromImage(image);
	}

	static void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2* points, Vector2* texcoords, int pointCount, Color tint)
	{
		rlSetTexture(texture.id);

		// Texturing is only supported on RL_QUADS
		rlBegin(RL_QUADS);

		rlColor4ub(tint.r, tint.g, tint.b, tint.a);

		for (int i = 0; i < pointCount - 1; ++i) {
			rlTexCoord2f(0.5f, 0.5f);
			rlVertex2f(center.x, center.y);

			rlTexCoord2f(texcoords[i].x, texcoords[i].y);
			rlVertex2f(points[i].x, points[i].y);

			rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
			rlVertex2f(points[i + 1].x, points[i + 1].y);

			rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
			rlVertex2f(points[i + 1].x, points[i + 1].y);
		}

		rlTexCoord2f(0.5f, 0.5f);
		rlVertex2f(center.x, center.y);

		rlTexCoord2f(texcoords[pointCount - 1].x, texcoords[pointCount - 1].y);
		rlVertex2f(points[pointCount - 1].x, points[pointCount - 1].y);

		rlTexCoord2f(texcoords[0].x, texcoords[0].y);
		rlVertex2f(points[0].x, points[0].y);

		rlTexCoord2f(texcoords[0].x, texcoords[0].y);
		rlVertex2f(points[0].x, points[0].y);

		rlEnd();

		rlSetTexture(0);
	}


	static std::pair<float, float> GetMinAndSize(const std::vector<Vector2>& vertices, std::function<float(const Vector2&)>&& lambda)
	{
		float min = INFINITY;
		float max = -INFINITY;

		for (auto& vertex : vertices) {
			min = std::min(min, lambda(vertex));
			max = std::max(max, lambda(vertex));
		}

		return { min, max - min };
	}

	void Renderable::DrawTexture() const
	{
		auto min_x_width = GetMinAndSize(_geometry->GetVertices(), [](const Vector2& v) { return v.x; });
		auto min_y_height = GetMinAndSize(_geometry->GetVertices(), [](const Vector2& v) { return v.y; });

		std::vector<Vector2> tex_coords(_geometry->GetVertices().size());
		for (int i = 0; i < tex_coords.size(); ++i)
		{
			auto x_origin = (_geometry->GetVertices()[i].x - min_x_width.first);
			auto y_origin = (_geometry->GetVertices()[i].y - min_y_height.first);
			auto factor_x = x_origin == 0 ? 0 : 1;
			auto factor_y = y_origin == 0 ? 0 : 1;

			// Normalize [0, 1]
			tex_coords[i] = {
				(x_origin * factor_x) / min_x_width.second,
				(y_origin * factor_y) / min_y_height.second
			};
		}

		DrawTexturePoly(_texture, _geometry->GetCenter(), (Vector2*)_geometry->GetVertices().data(), (Vector2*)tex_coords.data(), tex_coords.size(), _color);
	}

	void Renderable::DrawBase() const
	{
		switch (_geometry->GetKind())
		{
		case Geometry::Kind::CIRCLE:
			{
				auto circle = static_cast<Circle*>(_geometry);
				DrawCircleV(_geometry->GetPosition(), circle->GetRadius(), _color);
				break;
			}
		default:
			DrawTriangleFan((Vector2*)_geometry->GetVertices().data(), _geometry->GetVertices().size(), _color);
			break;
		}
	}

	void Renderable::Draw() const
	{
		if (_image.data != nullptr) {
			DrawTexture();
		}
		else {
			DrawBase();
		}
	}
}
