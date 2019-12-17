#include "World.h"


void px::World::step(double dt_MicroSeconds)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].getPhysicsType() != PhysicsObject::Static)
			objects[i].update(dt_MicroSeconds);
	}
}

std::vector<std::pair<px::PhysicsObject&, px::PhysicsObject&>> px::World::getCollisions()
{
	std::vector<std::pair<PhysicsObject&, PhysicsObject&>> collisions;
	for (auto& obj : objects)
	{
		
	}
}

void px::World::RespondToCollisions()
{
}

void px::World::clampObjects()
{
}

px::World::World()
{
}


px::World::~World()
{
}

void px::World::update(double dt_MicroSeconds)
{
	auto collisions = getCollisions();

	step(dt_MicroSeconds);
	clampObjects();
	RespondToCollisions();
}

void px::World::addObject(const Shape& shape, const Vector2f & position, const Vector2f & velocity, const Mass & m) //Dynamic
{
	if (shape.getType() == Shape::Circle)
	{
		objects.emplace_back(position, velocity, m, new CircleShape(dynamic_cast<const CircleShape&>(shape))); //PhysicsObject(Vector2f position, Vector2f velocity, Mass mass, Shape* new_shape); //Dynamic
	}
	else if (shape.getType() == Shape::Polygon)
	{
		objects.emplace_back(position, new PolygonShape(dynamic_cast<const PolygonShape&>(shape)), velocity);
	}
	else
	{
		assert(false);
	}
}

void px::World::addObject(const Shape& shape, const Vector2f & position, const Vector2f & velocity) //Kinematic
{
	if (shape.getType() == Shape::Circle)
	{
		objects.emplace_back(position, new CircleShape(dynamic_cast<const CircleShape&>(shape)), velocity); //PhysicsObject(Vector2f position, Shape* new_shape, Vector2f velocity); //Kinematic
	}
	else if (shape.getType() == Shape::Polygon)
	{
		objects.emplace_back(position, new PolygonShape(dynamic_cast<const PolygonShape&>(shape)), velocity);
	}
	else
	{
		assert(false);
	}
}

void px::World::addObject(const Shape& shape, const Vector2f & position) //Static
{
	if (shape.getType() == Shape::Circle)
	{
		objects.emplace_back(position, new CircleShape(dynamic_cast<const CircleShape&>(shape)));//Static
	}
	else if (shape.getType() == Shape::Polygon)
	{
		objects.emplace_back(position, new PolygonShape(dynamic_cast<const PolygonShape&>(shape)));
	}
	else
	{
		assert(false);
	}
}
