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

#include <SimuAPP/H/Button.h>


int main() {
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Counter button");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	int counter = 0;
	Button button({ screenWidth / 2 - 60, screenHeight / 2 - 30}, { 60, 30 });
	button.SetOnCick([&counter]() { counter += 1; });

	core::CollisionEngine::Instance().Init();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		core::DeltaTime delta;
		// Update
		//----------------------------------------------------------------------------------

		button.UpdateLogic();

		core::CollisionEngine::Instance().Update();

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText(std::to_string(counter).c_str(), 10, 10, 20, BLACK);
		button.UpdateDraw();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
}
