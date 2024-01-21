#pragma once

#include <string>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <SimuAPP/H/Element.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/Math.h>


class CarActor : public core::Actor {
public:

    CarActor()
    {
        _body.force = Vector2Zero();
        _body.form.SetSize({40, 40});
        _body.form.SetOrigin(_body.form.GetCenter());
        SetPosition({ 10, 10 });
        _body.color = RED;
        _body.velocity = 30.f;

        core::Collider collider;
        collider.SetGeometry(std::make_unique<core::Square>(_body.form));
        SetCollider(collider);
        EnableCollider();

        SetTag("Car");
    }

    void SetPropertiesImp(Actor::Properties properties) override
    {
    }

    void SetPositionImp(Vector2 pos) override
    {
        _body.form.SetPosition(pos);
    }

    void SetRotationImp(float rotation) override
    {
        _body.form.SetRotation(rotation);
    }

    void UpdatePhysics()
    {
    }

    void UpdateLogic() override
    {
        static const float rotation = 0.5f;

        if (IsKeyDown(KEY_W)) {
            float velo_delta = _body.velocity * core::DeltaTime::delta;
            Vector2 force_vector = { cos(GetRotation()) * velo_delta, sin(GetRotation()) * velo_delta};
            _body.force = force_vector;
            SetPosition(Vector2Add(GetPosition(), force_vector));
        }

        if (IsKeyDown(KEY_S)) {
            float velo_delta = _body.velocity * core::DeltaTime::delta;
            velo_delta *= -1;
            Vector2 force_vector = { cos(GetRotation()) * velo_delta, sin(GetRotation()) * velo_delta };
            _body.force = force_vector;
            SetPosition(Vector2Add(GetPosition(), force_vector));
        }

        if (IsKeyDown(KEY_D)) {
            SetRotation(GetRotation() + rotation * core::DeltaTime::delta);
        }
        
        if (IsKeyDown(KEY_A)) {
            SetRotation(GetRotation() - rotation * core::DeltaTime::delta);
        }
    }

    void UpdateDraw() override
    {
        DebugDrawDirectionLine();
        DrawTriangleFan((Vector2*)_body.form.GetVertices().data(), _body.form.GetVertices().size(), _body.color);
        DrawText(std::to_string(GetRotation()).c_str(), GetPosition().x, GetPosition().y, 20, BLUE);
    }

    void OnCollision(Actor* object) override
    {
    }

protected:
    struct Body {
        Color color;
        float velocity = 0;
        Vector2 force = {0, 0};
        core::Square form;
    };

    Body _body;
};