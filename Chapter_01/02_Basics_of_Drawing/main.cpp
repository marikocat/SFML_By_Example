#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Rendering the rectangle.");

	sf::RectangleShape rect(sf::Vector2f(128.0f, 128.0f));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(320, 240);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// Close window button clicked.
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		// Draw here.
		window.draw(rect); // Render our shape.
		window.display();

	}
}