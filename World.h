#pragma once
#include "Object.h"

namespace px
{
	class World : public Drawable
	{
	private:
		std::vector<PhysicsObject> objects;

		void step(double dt_MicroSeconds);
		std::vector<std::pair<PhysicsObject&, PhysicsObject&>> getCollisions();
		void RespondToCollisions();
		void clampObjects();
	public:
		World();
		~World();
		void update(double dt_MicroSeconds);
		void addObject(const Shape& shape, const Vector2f& position, const Vector2f& velocity, const Mass& m); // Dynamic
		void addObject(const Shape& shape, const Vector2f& position, const Vector2f& velocity); // Kinematic
		void addObject(const Shape& shape, const Vector2f& position); // Static
		void remObject(const PhysicsObject& obj) {
			for (auto it = objects.begin(); it != objects.end(); it++) {
				if (&(*it) == &obj) {
					objects.erase(it);
					break;
				}
			}
		}
		void clear() {
			objects.clear();
		}
		const std::vector<PhysicsObject>& getObjects() const { return objects; }
		void draw() { for (auto& obj : objects) obj.draw(); }
	};
}