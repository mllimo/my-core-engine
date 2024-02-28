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

class Wall : public core::Actor {
public:

	Wall(Vector2 position, Vector2 size)
		: core::Actor()
		, _body(position, size)
		, _render(&_body)
	{
		SetPosition(position);
		_body.SetSize(size);
		core::Collider collider;

		collider.SetGeometry(_body);
		SetCollider(std::move(collider));

		SetTag("Wall");
		_render.SetColor(BLUE);

		EnableCollider();
		_properties.b2_properties.body->SetType(b2BodyType::b2_kinematicBody);
	}

	void SetPositionImp(Vector2 pos) override
	{
		_body.SetPosition(pos);
	}

	void SetRotationImp(float rotation) override
	{
		_body.SetRotation(rotation);
	}

	void UpdateDraw() override
	{
		_render.Draw();
	}

protected:
	core::Square _body;
	core::Renderable _render;
};