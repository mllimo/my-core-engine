#pragma once

#include <vector>
#include <deque>
#include <string>

#include <CoreAPI.h>
#include <Core/H/Actor.h>
#include <Core/H/DeltaTime.h>
#include <Core/H/CollisionEngine.h>

namespace core {
	class CORE_EXPORT APP {
	public:
		APP();
		virtual ~APP();

		int Main(int argc, char** argv);

		int GetScreenWidth() const { return _screen_width; }
		int GetScreenHeight() const { return _screen_height; }
		const std::string& GetWindowName() const { return _window_name; }

		void SetScreenWidth(int width);
		void SetScreenHeight(int height);
		void SetWindowName(const std::string& name);

		const std::vector<std::string>& GetArgs() const { return _args; }

		// returns true if the element was removed
		bool RemoveActor(Actor* actor);

		// returns true if the element was inserted
		bool AddActor(std::shared_ptr<Actor> actor);

	protected:
		// Implement it when you want to draw something out of actors scope
		virtual void UserDraw() {}

	private:
		int _screen_width = 800;
		int _screen_height = 450;
		std::string _window_name = "";
		std::vector<std::string> _args;	
		std::deque<std::shared_ptr<Actor>> _actors; //< TODO: Improve this with a Dat.Str with better searching complexity

		void Update();
		void Draw();
	};
}
