#include <iostream>
#include <chrono>
#include <memory>

#include <raylib.h>
#include <raymath.h>

#include <box2d/box2d.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/CollisionEngine.h>

#include <SimuAPP/H/Car.h>
#include <SimuAPP/H/Ball.h>

class Wall : public core::Actor {
public:
    Wall()
    {
        _body.SetSize({20, 20});
        _body.SetOrigin(_body.GetCenter());
        _color = RED;

        core::Collider collider(_body);
        SetCollider(std::move(collider));
        EnableCollider();

        SetPosition({200, 100});
        SetTag("Wall");
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
        if (core::CollisionEngine::Instance().AreColliding(this, "Car"))
            _color = GREEN;
        else
            _color = RED;
    }

    void UpdateDraw() override
    {
        DrawTriangleFan((Vector2*)_body.GetVertices().data(), _body.GetVertices().size(), _color);
    }

private:
    core::Square _body;
    Color _color;
    bool _collided = false;
};

#if 1
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    CarActor car;
    Wall wall;

    core::CollisionEngine::Instance().Init();

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        core::DeltaTime delta;
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        car.UpdateLogic();
        //wall.UpdateLogic();

        core::CollisionEngine::Instance().Update();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //actor.UpdateDraw();
        car.UpdateDraw();
        wall.UpdateDraw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
#endif