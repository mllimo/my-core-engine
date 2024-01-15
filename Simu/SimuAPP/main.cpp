#include <iostream>
#include <chrono>
#include <memory>

#include <raylib.h>
#include <raymath.h>

#include <Core/H/Element.h>
#include <Core/H/DeltaTime.h>
#include <Core/H/Object.h>
#include <Core/H/CollisionEngine.h>

class ElementActor : public core::Object {
public:

    ElementActor(std::unique_ptr<core::Element> element)
    {
        _element = std::move(element);
        _properties.position = _element->GetProperties().position;
        _properties.collider = _element->GetProperties().size;
        EnableToCollide();
    }

    void UpdateLogic() override
    {
        _element->GetProperties().position = Vector2Add(_element->GetProperties().position, Vector2Scale(_element->GetProperties().force, core::DeltaTime::delta));
        _properties.position = _element->GetProperties().position;
    }

    void UpdateDraw() override
    {
        DrawRectangleV(_properties.position, _element->GetSize(), _element->GetColor());
    }

    void OnCollision(Object* object) override
    {
        _element->GetProperties().force = { 0, 0 };
    }

protected:
    std::unique_ptr<core::Element> _element;

};

int main() {
// Initialization
//--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    core::Element maroon;
    maroon.SetColor(MAROON);
    maroon.SetPosition({ 100, 100 });
    maroon.SetSize({ 20, 20 });
    maroon.GetProperties().force = {10, 0};

    core::Element toto;
    toto.SetColor(MAROON);
    toto.SetPosition({ 500, 100 });
    toto.SetSize({ 20, 20 });
    toto.GetProperties().force = { -10, 0 };

    ElementActor actor(std::make_unique<core::Element>(std::move(maroon)));
    ElementActor actor2(std::make_unique<core::Element>(std::move(toto)));

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        auto start = std::chrono::high_resolution_clock::now();
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        actor.UpdateLogic();
        actor2.UpdateLogic();


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        core::CollisionEngine::Update();
        actor.UpdateDraw();
        actor2.UpdateDraw();

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
