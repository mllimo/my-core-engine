#pragma once

#include <string>
#include <functional>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/Math.h>
#include <Core/H/CollisionEngine.h>
#include <Core/H/Renderable.h>

class Button : public core::Actor {
public:

	Button(Vector2 position, Vector2 size)
		: core::Actor()
		, _body(position, size)
		, _render(&_body)
	{
		SetPosition(position);

		core::Collider collider;

		collider.SetGeometry(_body);
		SetCollider(std::move(collider));

		SetTag("Button");
		_render.SetColor(GREEN);
	}

	void SetOnCick(std::function<void(void)> lambda)
	{
		_on_click = lambda;
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
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			core::Circle raycast(GetMousePosition(), 2);
			core::Collider mouse_collider(raycast);

			if (GetCollider().IsColliding(mouse_collider)) {
				if (_on_click) _on_click();
			}
		}
	}

	void UpdateDraw() override
	{
		_render.Draw();
	}

protected:
	core::Square _body;
	core::Renderable _render;
	std::function<void(void)> _on_click;
};