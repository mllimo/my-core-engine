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

#include <PingPong/H/Racket.h>
#include <PingPong/H/Ball.h>
#include <PingPong/H/Wall.h>

// TODO: Improve the example with a better pong game :D
class PingPongAPP : public core::APP, public core::Singleton<PingPongAPP>
{
public:
	void Init() override
	{
		std::shared_ptr<Racket> racket_ptr(new Racket({ 30, _screen_height / 2.f - 30.f}, { 30.f, 60.f }));
		_racket = racket_ptr;

		std::shared_ptr<Racket> racket2_ptr(new Racket({ _screen_width - 60.f, _screen_height / 2.f - 30.f }, { 30.f, 60.f }));
		_racket2 = racket2_ptr;

		std::shared_ptr<Wall> top_wall_ptr(new Wall( { 0.f, 0.f }, { (float)_screen_width, 30.f} ));
		_top_wall = top_wall_ptr;

		std::shared_ptr<Wall> bot_wall_ptr(new Wall({ 0.f, (float)_screen_height - 30}, { (float)_screen_width, 30.f }));
		_bot_wall = bot_wall_ptr;

		std::shared_ptr<Ball> ball_ptr(new Ball({ _screen_width / 2.f, _screen_height / 2.f }, 30.f));
		_ball = ball_ptr;

		AddActor(std::move(ball_ptr));

		AddActor(std::move(racket_ptr));
		AddActor(std::move(racket2_ptr));

		AddActor(std::move(top_wall_ptr));
		AddActor(std::move(bot_wall_ptr));
	}

private:
	const int _screen_width = 800;
	const int _screen_height = 450;

	std::weak_ptr<Ball> _ball;

	std::weak_ptr<Racket> _racket;
	std::weak_ptr<Racket> _racket2;

	std::weak_ptr<Wall> _top_wall;
	std::weak_ptr<Wall> _bot_wall;
};

int main(int argc, char** argv) {
	PingPongAPP::Instance().Init();
	return PingPongAPP::Instance().Main(argc, argv);
}
