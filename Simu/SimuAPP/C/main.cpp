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
    }

    void OnCollision(Actor* other)
    {
        _color = GREEN;
    }

    void UpdateDraw() override
    {
        DrawTriangleFan((Vector2*)_body.GetVertices().data(), _body.GetVertices().size(), _color);
    }

private:
    core::Square _body;
    Color _color;
};

namespace repro {
    bool IsColliding(const std::vector<Vector2>& vertices, const std::vector<Vector2>& other_vertices)
    {
        if (vertices.size() == 0 || other_vertices.size() == 0) return false;

        auto& bigger_vertices_vector = (vertices.size() >= other_vertices.size()
            ? vertices
            : other_vertices
            );

        auto& lower_vertices_vector = (other_vertices.size() <= vertices.size()
            ? other_vertices
            : vertices
            );

        for (const auto& vertex : lower_vertices_vector) {
            if (CheckCollisionPointPoly(vertex, (Vector2*)bigger_vertices_vector.data(), bigger_vertices_vector.size()))
                return true;
        }

        // When vertices are not in the area of the poly
        for (long i = (long)bigger_vertices_vector.size() - 1; i >= 0; i -= 1) {
            if (i - 1 < 0) break;
            Vector2 i_A = bigger_vertices_vector[i];
            Vector2 i_B = bigger_vertices_vector[i - 1ll];

            for (long j = (long)lower_vertices_vector.size() - 1; j >= 0; j -= 1) {
                if (j - 1 < 0) break;
                Vector2 j_A = lower_vertices_vector[j];
                Vector2 j_B = lower_vertices_vector[j - 1ll];

                Vector2 dummy;
                if (CheckCollisionLines(i_A, i_B, j_A, j_B, &dummy))
                    return true;
            }
        }

        return false;
    }
}


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