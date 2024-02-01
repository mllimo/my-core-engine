#include <Core/H/CollisionEngine.h>

#include <unordered_set>

namespace core {

	std::deque<Actor*> CollisionEngine::_objects = {};
	std::unordered_map<Actor*, std::unordered_set<Actor*>> CollisionEngine::_collision_map = {};

	void CollisionEngine::Add(Actor* object)
	{
		_objects.emplace_back(object);
	}

	void CollisionEngine::Remove(Actor* object)
	{
		auto found_it = std::find(_objects.begin(), _objects.end(), object);
		if (found_it == _objects.end()) return;
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

	struct Projection {
		float min;
		float max;
	};

	static Projection Project(const std::vector<Vector2>& vertices, const Vector2& axis) {
		float dotProduct = Vector2DotProduct(axis, vertices[0]);
		Projection result{ dotProduct, dotProduct };

		for (const auto& vertex : vertices) {
			float dotProduct = Vector2DotProduct(axis, vertex);
			result.min = std::min(result.min, dotProduct);
			result.max = std::max(result.max, dotProduct);
		}

		return result;
	}

	static bool Overlapping(const Projection& p1, const Projection& p2) {
		return !(p1.max < p2.min || p2.max < p1.min);
	}

	std::vector<Vector2> GetAxes(const Collider& collider_a, const Collider& collider_b) {
		std::vector<Vector2> axes;
		auto& vertices_a = collider_a.GetGeometry().GetVertices();
		auto& vertices_b = collider_b.GetGeometry().GetVertices();

		// Agrega ejes para las aristas de la primera figura
		for (size_t i = 0; i < vertices_a.size(); ++i) {
			Vector2 edge = Vector2Subtract(vertices_a[(i + 1) % vertices_a.size()], vertices_a[i]);
			axes.push_back(Vector2Normalize({ -edge.y, edge.x }));
		}

		// Agrega ejes para las aristas de la segunda figura
		for (size_t i = 0; i < vertices_b.size(); ++i) {
			Vector2 edge = Vector2Subtract(vertices_b[(i + 1) % vertices_b.size()], vertices_b[i]);
			axes.push_back(Vector2Normalize({ -edge.y, edge.x }));
		}

		return axes;
	}

	static Vector2 FindSeparationVector(const Collider& collider_a, const Collider& collider_b) {
		std::vector<Vector2> axes = GetAxes(collider_a, collider_b);

		Vector2 separationVector = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };

		for (const auto& axis : axes) {
			Projection projection1 = Project(collider_a.GetGeometry().GetVertices(), axis);
			Projection projection2 = Project(collider_b.GetGeometry().GetVertices(), axis);

			if (!Overlapping(projection1, projection2)) {
				// Las proyecciones no se superponen en este eje, por lo que no hay colisión
				return Vector2(0.0f, 0.0f);
			}

			// Calcula el mínimo vector de separación entre las proyecciones
			float overlap = std::min(projection1.max, projection2.max) - std::max(projection1.min, projection2.min);
			Vector2 axisVector = Vector2Scale(axis, overlap);

			// Actualiza el vector de separación mínimo
			if (overlap < Vector2Length(separationVector)) {
				separationVector = axisVector;
			}
		}

		return separationVector;
	}

	static void Resolve(Actor* actor_a, Actor* actor_b)
	{
		Vector2 separation = FindSeparationVector(actor_a->GetCollider(), actor_b->GetCollider());
		actor_a->SetPosition(Vector2Add(actor_a->GetPosition(), separation));
		actor_b->SetPosition(Vector2Subtract(actor_b->GetPosition(), separation));
	}

	void CollisionEngine::Update()
	{
		_collision_map.clear();
		for (auto it = _objects.begin(); it != _objects.end(); ++it) {
			for (auto jt = std::next(it); jt != _objects.end(); ++jt) {
				auto collider_i = (*it)->GetCollider();
				auto collider_j = (*jt)->GetCollider();

				if (collider_i.IsColliding(collider_j)) {
					_collision_map[*it].insert(*jt);
					_collision_map[*jt].insert(*it);
					Resolve(*it, *jt);
				}

			}
		}
	}
}
