#include "World.h"
using namespace px;
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 32;
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Default, settings);
	World wrld;
	{
		std::vector<Vector2f> points;
		for (Angle a = Angle::angle(0); a.deg() < 360; a += Angle::angle(360 / 5))
		{
			points.emplace_back(Vector2f{ 50 * cosf(a.rad()),50 * sinf(a.rad()) });
		}
		PolygonShape ps(points);
		wrld.addObject(ps, px::Vector2f(400, 300), px::Vector2f(10, -2));
	}
	Shape::window = &window;
	sf::Clock clock;
	sf::Time dt;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		wrld.update(dt.asMicroseconds());
		window.clear();
		for (auto& obj : wrld.getObjects())
		{
			obj.draw();
		}
		window.display();
		dt = clock.restart();
	}
	return 0;
}