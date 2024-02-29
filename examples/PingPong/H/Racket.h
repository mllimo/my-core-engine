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

class Racket : public core::Actor {
public:

	Racket(Vector2 position, Vector2 size)
		: core::Actor()
		, _body(position, size)
		, _render(&_body)
	{
		SetPosition(position);
		core::Collider collider;

		collider.SetGeometry(_body);
		SetCollider(std::move(collider));

		SetTag("Racket");
		_render.SetColor(BLACK);

		EnableCollider();
		_properties.b2_properties.body->SetType(b2BodyType::b2_kinematicBody);
		_properties.b2_properties.body->SetFixedRotation(true);
	}

	void SetUpKey(KeyboardKey key)
	{
		_up = key;
	}

	void DownKey(KeyboardKey key)
	{
		_down = key;
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
		if (IsKeyDown(_up)) {
			_properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(Vector2{ 0, -_move_speed * core::DeltaTime::delta }));
		} else if (IsKeyDown(_down)) {
			_properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(Vector2{ 0, _move_speed * core::DeltaTime::delta }));
		}
		else {
			_properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(Vector2Zero()));
		}
	}

	void UpdateDraw() override
	{
		_render.Draw();
	}

protected:
	core::Square _body;
	core::Renderable _render;
	float _move_speed = 50;
	KeyboardKey _up = KEY_W;
	KeyboardKey _down = KEY_S;

};