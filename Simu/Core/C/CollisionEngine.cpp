#include <Core/H/CollisionEngine.h>
#include <Core/H/DeltaTime.h>

#include <iostream>
#include <unordered_set>

namespace core {

	b2World CollisionEngine::_world(b2Vec2(0, 9));
	std::deque<Actor*> CollisionEngine::_objects = {};
	std::unordered_map<Actor*, std::unordered_set<Actor*>> CollisionEngine::_collision_map = {};

	class Listener : public b2ContactListener {
		void BeginContact(b2Contact* contact) override
		{
			std::cout << "asdads";
		}
	};

	void CollisionEngine::Init()
	{
		_world.SetContactListener(new Listener);
	}

	void CollisionEngine::Add(Actor* object)
	{
		b2BodyDef def;
		def.type = b2_dynamicBody;
		def.position.Set(object->_properties.position.x, object->_properties.position.y);
		def.angle = object->_properties.rotation;
		object->_properties.b2_properties.body = _world.CreateBody(&def);

		std::unique_ptr<b2Shape> aux_ptr(object->GetCollider().GetGeometry().ConstructB2FromThis());
		object->_properties.b2_properties.fixture = object->_properties.b2_properties.body->CreateFixture(aux_ptr.get(), 1);
		object->_properties.collider._geometry->_b2_shape = dynamic_cast<b2PolygonShape*>(object->_properties.b2_properties.fixture->GetShape());

		_objects.emplace_back(object);
	}

	void CollisionEngine::Remove(Actor* object)
	{
		auto found_it = std::find(_objects.begin(), _objects.end(), object);
		if (found_it == _objects.end()) return;

		_world.DestroyBody(object->_properties.b2_properties.body);
		object->_properties.b2_properties.body = nullptr;

		_objects.erase(found_it);
	}

	bool CollisionEngine::AreColliding(Actor* a, Actor* b)
	{
		auto exist_a = _collision_map.find(a);
		if (exist_a == _collision_map.end()) return false;
		auto collide_with_b = _collision_map.find(b);
		return collide_with_b != _collision_map.end();
	}

	bool CollisionEngine::AreColliding(Actor* a, std::string_view tag)
	{
		auto exist_a = _collision_map.find(a);
		if (exist_a == _collision_map.end()) return false;

		for (const auto& actor : exist_a->second) {
			if (actor->GetTag() == tag) return true;
		}

		return false;
	}
		
	void CollisionEngine::Update()
	{
		static const int32_t velocity_iterations = 6;
		static const int32_t position_iterations = 2;
		_world.Step(DeltaTime::delta, velocity_iterations, position_iterations);

		for (auto* actor : _objects) {
			actor->UpdateFromB2();
		}
	}
}
