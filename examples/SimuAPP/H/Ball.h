#pragma once

#include <string>

#include <Core/H/Actor.h>

class Ball : public core::Actor {
public:
	Ball(Vector2 position, float radius)
	{
		_body = core::Circle(position, radius);
		_color = RED;

		SetTag("Ball");
		SetPosition(position);

		SetCollider({_body});
		EnableCollider();
	}

	void SetPositionImp(Vector2 pos) override
	{
		_body.SetPosition(pos);
	}

	void SetRotationImp(float rotation) override
	{
		_body.SetRotation(rotation);
	}

	void UpdateLogic() override
	{
		if (IsMouseButtonDown(MouseButton::MOUSE_BUTTON_LEFT)) {
			Vector2 pos = GetMousePosition();
			core::Collider collider;
			collider.SetGeometry(std::make_unique<core::Circle>(pos, 1));
			if (GetCollider().IsColliding(collider)) {
				_counter += 1;
			}
		}
	}

	void UpdateDraw() override
	{
		DrawText(std::to_string(_counter).c_str(), 10, 30, 10, BLACK);
		DrawCircleV(GetPosition(), _body.GetRadius(), _color);
	}

private:
	core::Circle _body;
	int _counter = 0;
	Color _color;
};
