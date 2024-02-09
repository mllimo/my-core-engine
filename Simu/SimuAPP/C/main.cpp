#include <iostream>
#include <chrono>
#include <memory>
#include <filesystem>

#include <raylib.h>
#include <raymath.h>

#include <box2d/box2d.h>

#include <Core/H/DeltaTime.h>
#include <Core/H/Actor.h>
#include <Core/H/CollisionEngine.h>
#include <Core/H/Renderable.h>

#include <SimuAPP/H/Car.h>
#include <SimuAPP/H/Ball.h>

class Wall : public core::Actor {
public:
	Wall() : _render_body(&_body)
	{
		_body.SetSize({ 100, 100 });
		_body.SetOrigin(_body.GetCenter());
		_render_body.SetColor(WHITE);
		auto image = LoadImage("wall.png");
		_render_body.SetTexture(std::move(image));

		core::Collider collider(_body);
		SetCollider(std::move(collider));
		EnableCollider();

		SetPosition({ 200, 100 });
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
		_render_body.Draw();
		//DrawTriangleFan((Vector2*)_body.GetVertices().data(), _body.GetVertices().size(), _color);
	}

private:
	core::Square _body;
	core::Renderable _render_body;
	Color _color;
	bool _collided = false;
};

#if 1
int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	CarActor car;
	Wall wall;

	core::CollisionEngine::Instance().Init();

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
#else
#define MAX_POINTS  11      // 10 points and back to the start

// Draw textured polygon, defined by vertex and texture coordinates
void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2* points, Vector2* texcoords, int pointCount, Color tint);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - textured polygon");

    // Define texture coordinates to map our texture to poly
    Vector2 texcoords[MAX_POINTS] = {
        { 0.75f, 0.0f },
		{ 0.25f, 0.0f },
		{ 0.0f, 0.5f },
 {
0.0f, 0.75f
},
 {
0.25f, 1.0f
},
 {
0.375f, 0.875f
},
 {
0.625f, 0.875f
},
 {
0.75f, 1.0f
},
 {
1.0f, 0.75f
},
 { 1.0f, 0.5f },
{ 0.75f, 0.0f }  // Close the poly
    };

    // Define the base poly vertices from the UV's
    // NOTE: They can be specified in any other way
    Vector2 points[MAX_POINTS] = { 0 };
    for (int i = 0; i < MAX_POINTS; i++)
    {
        points[i].x = (texcoords[i].x - 0.5) * 256.0f;
        points[i].y = (texcoords[i].y - 0.5) * 256.0f;
    }

    // Define the vertices drawing position
    // NOTE: Initially same as points but updated every frame
    Vector2 positions[MAX_POINTS] = { 0 };
    for (int i = 0; i < MAX_POINTS; i++) positions[i] = points[i];

    // Load texture to be mapped to poly
    Texture texture = LoadTexture("wall.png");

    float angle = 0.0f;             // Rotation angle (in degrees)

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Update points rotation with an angle transform
        // NOTE: Base points position are not modified
        //angle++;
        //for (int i = 0; i < MAX_POINTS; i++) positions[i] = Vector2Rotate(points[i], angle * DEG2RAD);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("textured polygon", 20, 20, 20, DARKGRAY);

        DrawTexturePoly(texture, { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
            positions, texcoords, MAX_POINTS, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture); // Unload texture

    CloseWindow();          // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Draw textured polygon, defined by vertex and texture coordinates
// NOTE: Polygon center must have straight line path to all points
// without crossing perimeter, points must be in anticlockwise order
void DrawTexturePoly(Texture2D texture, Vector2 center, Vector2* points, Vector2* texcoords, int pointCount, Color tint)
{
    rlSetTexture(texture.id);

    // Texturing is only supported on RL_QUADS
    rlBegin(RL_QUADS);

    rlColor4ub(tint.r, tint.g, tint.b, tint.a);

    for (int i = 0; i < pointCount - 1; i++)
    {
        rlTexCoord2f(0.5f, 0.5f);
        rlVertex2f(center.x, center.y);

        rlTexCoord2f(texcoords[i].x, texcoords[i].y);
        rlVertex2f(points[i].x + center.x, points[i].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);

        rlTexCoord2f(texcoords[i + 1].x, texcoords[i + 1].y);
        rlVertex2f(points[i + 1].x + center.x, points[i + 1].y + center.y);
    }
    rlEnd();

    rlSetTexture(0);
}
#endif

