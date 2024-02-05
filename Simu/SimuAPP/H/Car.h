#pragma once

#include <string>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/Math.h>
#include <Core/H/CollisionEngine.h>


class CarActor : public core::Actor {
public:

    CarActor()
    {
        _body.force = Vector2Zero();
        _body.form.SetSize({40, 40});
        _body.form.SetOrigin(_body.form.GetCenter());
        _body.color = RED;
        _body.velocity = 100.f;

        core::Collider collider;
        collider.SetGeometry(std::make_unique<core::Square>(_body.form));
        SetCollider(std::move(collider));
        EnableCollider();

        SetPosition({ 100, 100 });
        SetTag("Car");

        _properties.b2_properties.fixture->SetDensity(100.f);
    }

    void SetPropertiesImp(const Actor::Properties& properties) override
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

        if (core::CollisionEngine::AreColliding(this, "Wall"))
            TraceLog(LOG_INFO, "Car vs Wall");

        if (IsKeyDown(KEY_W)) {
            float velo_delta = _body.velocity * core::DeltaTime::delta;
            Vector2 force_vector = { cos(GetRotation()), sin(GetRotation())};
            _properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(force_vector));
            //_body.force = force_vector;
            //SetPosition(Vector2Add(GetPosition(), force_vector));
        }

        if (IsKeyDown(KEY_S)) {
            float velo_delta = _body.velocity * core::DeltaTime::delta;
            Vector2 force_vector = { cos(GetRotation()) * -1, sin(GetRotation()) * -1};
            _properties.b2_properties.body->SetLinearVelocity(core::ToB2Vetor2(force_vector));
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

protected:
    struct Body {
        Color color;
        float velocity = 0;
        Vector2 force = {0, 0};
        core::Square form;
    };

    Body _body;
};