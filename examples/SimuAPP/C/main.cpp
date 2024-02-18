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
#include <Core/H/Singleton.h>
#include <Core/H/APP.h>

#include <SimuAPP/H/Button.h>

class ButtonAPP : public core::APP, public core::Singleton<ButtonAPP>
{
public:
	void Init() override
	{
		std::shared_ptr<Button> button_ptr(new Button({ _screen_width / 2.f - 60.f, _screen_height / 2.f - 30.f}, { 60.f, 30.f }));
		_button = button_ptr;
		_button.lock()->SetOnCick([this]() { _counter += 1; });
		AddActor(std::move(button_ptr));
	}

	void UserDraw() override
	{
		DrawText(std::to_string(_counter).c_str(), 10, 10, 20, BLACK);
	}

private:
	const int _screen_width = 800;
	const int _screen_height = 450;
	int _counter = 0;
	std::weak_ptr<Button> _button;
};

int main(int argc, char** argv) {
	return ButtonAPP::Instance().Main(argc, argv);
}
