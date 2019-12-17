#pragma once
#include "System.h"

namespace px
{
	class Entity
	{
	public:
		virtual const std::string getName() const { return "Entity"; }
	};

	class Shape : public Entity , public Drawable
	{
	public:
		enum Type
		{
			Circle = 0,
			Polygon = 1,
			Typeless
		};

	protected:
		const Type shapeType;
	public:
		virtual ~Shape() {}
		Shape(const Type shapeType) : shapeType(shapeType) {}
		const Type& getType() const { return shapeType; }
		virtual const std::string getName() const override { return "Shape"; }
		virtual void draw(const px::Vector2<int>& position = { 0, 0 }) const = 0;
	};

	class CircleShape : public Shape
	{
	public:
	protected:
		const float radius;
	public:
		CircleShape(const float& radius);
		virtual ~CircleShape() {}
		virtual const std::string getName() const override { return "CircleShape"; }
		const float& getRadius() const { return radius; }
		void draw(const px::Vector2<int>& position = { 0, 0 }) const override;
	};

	class PolygonShape : public Shape
	{
	public:
	protected:
		const std::vector<Vector2f> vertices;
	public:
		PolygonShape(const std::vector<Vector2f>& vertices);
		const std::vector<Vector2f>& getVertices() const { return vertices; };
		void draw(const px::Vector2<int>& position = { 0, 0 }) const override;
		virtual const std::string getName() const override { return "PolygonShape"; }
	};

	class PhysicsObject : public Entity, public Drawable
	{
	private:
	public:
		enum Type
		{
			Static, Kinematic, Dynamic
		};
	protected:
		Vector2f position, velocity;
		Angle rotation;
		const Shape* shape;
		const Type physicsType;
		const Mass mass;
	public:
		PhysicsObject(const Vector2f& position, const Vector2f& velocity, const Mass& mass, const Shape* shape); //Dynamic
		PhysicsObject(const Vector2f& position, const Shape* shape); //Static
		PhysicsObject(const Vector2f& position, const Shape* shape, const Vector2f& velocity); //Kinematic
		~PhysicsObject() { delete shape; }
		const IntersectData intersect(const PhysicsObject& other) const;
		virtual const std::string getName() const override { return "PhysicsObject"; }
		const Vector2f getPos() const { return position; }
		const Vector2f getVel() const { return velocity; }
		const Shape* getShapePtr() const { return shape; }
		const Type& getPhysicsType() { return physicsType; }
		void draw() const { shape->draw(px::Vector2<int>(position.x, position.y)); }
		void update(double dt_MicroSeconds);
		void applyForce(double duration_MicroSeconds, px::Vector2f force);
	};

}

