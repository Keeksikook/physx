#include "Object.h"

sf::RenderWindow* px::Drawable::window = nullptr;

px::CircleShape::CircleShape(const float& radius)
	:
	Shape(Shape::Type::Circle),
	radius(radius)
{
}

void px::CircleShape::draw(const px::Vector2<int>& position) const 
{
	sf::CircleShape circle;
	circle.setRadius(this->getRadius());
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(sf::Vector2f(position.x, position.y));
	circle.setFillColor(sf::Color(255, 255, 255, 25.5));
	window->draw(circle);
}

px::PhysicsObject::PhysicsObject(const Vector2f& position, const Vector2f& velocity, const Mass& mass, const Shape* shape)
	:
	PhysicsObject(position, shape)
	
{
	this->velocity = velocity;
	this->mass = mass;
	this->physicsType = Dynamic;
}

px::PhysicsObject::PhysicsObject(const Vector2f& position, const Shape* shape)
	:
	shape(shape),
	position(position),
	physicsType(Static),
	velocity(0,0),
	rotation(0, Angle::Unit::DEG)

{
}

px::PhysicsObject::PhysicsObject(const Vector2f& position, const Shape* const shape, const Vector2f& velocity)
	:
	PhysicsObject(position, shape)
{
	this->velocity = velocity;
	this->physicsType = Kinematic;
}

const IntersectData px::PhysicsObject::intersect(const PhysicsObject& other) const 
/*
Checklist:
	Circle -> Circle	+
	Circle -> Polygon	-
	Polygon -> Polygon	-
*/
{
	if (this->getShapePtr()->getType() == Shape::Circle)
	{
		px::CircleShape* thisShape = (CircleShape*)this->getShapePtr();
		if (other.getShapePtr()->getType() == Shape::Circle) //Both circles
		{
			px::CircleShape* otherShape = (CircleShape*)other.getShapePtr(); //Cast to Circle
			float radiusDistance = thisShape->getRadius() + otherShape->getRadius();
			float centerDistance = (other.getPos() - this->getPos()).getMagnitude();
			return IntersectData(centerDistance < radiusDistance, centerDistance - radiusDistance);
		}
		else if (other.getShapePtr()->getType() == Shape::Polygon) //Other polygon
		{
			//Placeholder return
			return IntersectData(false, -1);
		}
		else
		{
			assert(false); //Throw error
		}
	}
	else if (this->getShapePtr()->getType() == Shape::Polygon)
	{
		px::PolygonShape* thisShape = (PolygonShape*)other.getShapePtr(); // Cast to Polygon
		//Placeholder return
		return IntersectData(false, -1);
	}
	else
	{
		assert(false); //Throw error
	}
	
}

void px::PhysicsObject::update(double dt_MicroSeconds)
{
	this->position += this->velocity * (float)dt_MicroSeconds/1000000;
}

void px::PhysicsObject::applyForce(double duration_MicroSeconds, px::Vector2f force)
{
	if(this->physicsType != Static)
		this->velocity += force * duration_MicroSeconds/1000000;		
}

px::PolygonShape::PolygonShape(const std::vector<Vector2f>& vertices)
	:
	Shape(Polygon), vertices(vertices)
{

}

void px::PolygonShape::draw(const px::Vector2<int>& position) const
{
	if (vertices.size() > 0)
	{
		sf::ConvexShape shape;
		shape.setPointCount(vertices.size());
		for (int i = 0; i < vertices.size(); i++)
		{
			shape.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
		}
		shape.setPosition(position.x, position.y);
		shape.setFillColor(sf::Color(255, 255, 255, 25.5));
		px::PolygonShape::window->draw(shape);
	}
}
