#pragma once
#include <iostream>
namespace px
{
	class Property
	{
	protected:
		double value;
		Property(double value) : value(value) {}
		Property() : value(0) {}
	public:
	};

	class Angle : public Property
	{
	public:
		enum Unit { RAD, DEG };
	private:
		Unit unit;
	public:
		static Unit defaultUnit;

		//Constructors
		Angle() {};
		Angle(double theta, Unit unit = defaultUnit);

		//QOL functions
		Angle& normalize(); // puts the angle in the range [0 : 360] degrees
		static Angle angle(float thetaDegrees); // Builds an angle in degrees

		//Getter functions
		const double rad() const;
		const double deg() const;

		//Operator overloads
		friend std::ostream& operator<<(std::ostream& cout, Angle theta);
		Angle& operator+=(Angle other);
		Angle operator+(Angle other);
	};

	class Mass : public Property
	{
	public:
		enum Unit {KG, G, TON};
	public:
		Unit unit;
		static Unit defaultUnit;

		const double kg(double mass, Unit unit = defaultUnit) const;
	};
}