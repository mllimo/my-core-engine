#include <iostream>
#include <chrono>
#include <memory>

#include <raylib.h>
#include <raymath.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/CollisionEngine.h>

#include <SimuAPP/H/Car.h>

class Wall : public core::Actor {
public:
    Wall()
    {
        _body.SetSize({20, 20});
        _body.SetPosition({100, 100});
        _color = RED;

        core::Collider collider;
        collider.SetGeometry(std::make_unique<core::Square>(_body));
        SetCollider(collider);
        EnableCollider();

        SetTag("Wall");
    }

    void UpdateLogic() override
    {
        if (core::CollisionEngine::AreColliding(this, "Car"))
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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Color color = RED;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        auto start = std::chrono::high_resolution_clock::now();
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        //actor.UpdateLogic();

        car.UpdateLogic();
        wall.UpdateLogic();

        core::CollisionEngine::Update();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //actor.UpdateDraw();
        car.UpdateDraw();
        wall.UpdateDraw();

        EndDrawing();
        //----------------------------------------------------------------------------------

        auto end = std::chrono::high_resolution_clock::now();
        auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        core::DeltaTime::delta = 1 / (diff == 0 ? 0.000000000000001f : diff);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
#endif