#include "System.h"

px::Angle::Unit px::Angle::defaultUnit = px::Angle::Unit::DEG;


px::Angle::Angle(double theta, Unit unit)
	:
	Property(theta),
	unit(unit)
{
}

px::Angle & px::Angle::normalize()
{
	if (unit == DEG)
		if (value > 360)
			value = fmod(value, 360);
		else
			while (value < 0)
				value += 360.0f;
	else
		if (value > 2 * PI)
			value = fmod(value, 2 * PI);
		else
			while (value < 0)
				value += 2 * PI;
	return *this;
}

px::Angle px::Angle::angle(float thetaDegrees)
{
	return Angle(thetaDegrees, Angle::Unit::DEG);
}

const double px::Angle::rad() const
{
	return ((unit == Unit::RAD) ? (value) : (value * PI / double(180)));
}

const double px::Angle::deg() const
{
	return ((unit == Unit::DEG) ? (value) : (value * double(180) / PI));
}

px::Angle & px::Angle::operator+=(Angle other)
{
	if (this->unit == DEG)
		this->value += other.deg();
	else
		this->value += other.rad();
	return *this;
}

px::Angle px::Angle::operator+(Angle other)
{
	if (unit == Angle::Unit::DEG)
		return Angle(this->value + other.deg(), DEG);
	else
		return Angle(this->value + other.rad(), RAD);
}

std::ostream & px::operator<<(std::ostream & cout, Angle theta)
{
	if (Angle::defaultUnit == Angle::Unit::DEG)
		cout << round(theta.deg()) << 'D';
	else
		cout << round(theta.rad()) << 'R';
	return cout;
}

void px::LineSegment::draw()
{
	assert(window != nullptr);
	sf::Vertex line[2] = {
		sf::Vector2f(start.x, start.y),
		sf::Vector2f(end.x, end.y)
	};
	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;
	window->draw(line, 2, sf::Lines);
}
