#include <Core/H/APP.h>

#include <raylib.h>

namespace core {

	APP::APP()
	{
		InitWindow(_screen_width, _screen_height, _window_name.c_str());
	}

	APP::~APP()
	{
	}

	void APP::SetScreenWidth(int width)
	{
		_screen_width = width;
		SetWindowSize(_screen_width, _screen_height);
	}

	void APP::SetScreenHeight(int height)
	{
		_screen_height = height;
		SetWindowSize(_screen_width, _screen_height);
	}

	void APP::SetWindowName(const std::string& name)
	{
		_window_name = name;
		SetWindowTitle(_window_name.c_str());
	}

	bool APP::RemoveActor(Actor* actor)
	{
		auto it = std::find_if(_actors.begin(), _actors.end(), [actor](auto& v) { return v.get() == actor; });
		if (it == _actors.end()) return false;
		_actors.erase(it);
		return true;
	}

	bool APP::AddActor(std::shared_ptr<Actor> actor)
	{
		auto it = std::find_if(_actors.begin(), _actors.end(), [&actor](auto& v) { return v.get() == actor.get(); });
		if (it != _actors.end()) return false;
		_actors.push_back(std::move(actor));
		return true;
	}

	void APP::Update()
	{
		for (auto& actor : _actors)
			actor->UpdateLogic();
	}

	void APP::Draw()
	{
		UserDraw();
		for (auto& actor : _actors)
			actor->UpdateDraw();
	}

	int APP::Main(int argc, char** argv)
	{
		_args.insert(_args.end(), argv, argv + argc);

		SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
		//--------------------------------------------------------------------------------------

		// Init Physics and Collision engine
		core::CollisionEngine::Instance().Init();

		// Main game loop
		while (!WindowShouldClose()) {
			core::DeltaTime delta;
			// Update
			//----------------------------------------------------------------------------------

			core::CollisionEngine::Instance().Update();

			// Call Update actor function
			Update();

			// Draw
			//----------------------------------------------------------------------------------
			BeginDrawing();

			ClearBackground(RAYWHITE);

			// Call Draw actor function
			Draw();

			EndDrawing();
			//----------------------------------------------------------------------------------
		}

		CloseWindow();

		return 0;
	}

}
