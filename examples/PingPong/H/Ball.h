#pragma once

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/Math.h>
#include <Core/H/CollisionEngine.h>
#include <Core/H/Renderable.h>

class Ball : public core::Actor {
public:

	Ball(Vector2 position, float radius) 
		: _body(position, radius)
		, _render(&_body) 
	{
		SetPosition(position);

		core::Collider collider(_body);
		SetCollider(std::move(collider));

		_render.SetColor(GREEN);

		EnableCollider();
		SetTag("Ball");
		_properties.b2_properties.body->SetType(b2_dynamicBody);
		_properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(Vector2{ 5, 0 }));
		_properties.b2_properties.fixture->SetRestitution(1.f);
	}

	void SetPositionImp(Vector2 pos) override
	{
		_body.SetPosition(pos);
	}

	void UpdateDraw()
	{
		_render.Draw();
	}

private:
	core::Circle _body;
	core::Renderable _render;
};
