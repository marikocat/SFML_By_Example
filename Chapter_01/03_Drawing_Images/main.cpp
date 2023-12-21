#include <SFML/Graphics.hpp>

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bouncing mushroom.");

	sf::Texture texture;
	if (!texture.loadFromFile("Mushroom.png"))
	{
		// Handle an error.
	}
	sf::Sprite sprite(texture);
	sf::Vector2u size = texture.getSize();
	sprite.setOrigin(size.x / 2, size.y / 2);
	sprite.setColor(sf::Color(255, 255, 255, 65)); // Red tint.
	sf::Vector2f increment(0.2f, 0.2f);

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

		if ((sprite.getPosition().x + (size.x / 2) > window.getSize().x && increment.x > 0) ||
			(sprite.getPosition().x - (size.x / 2) < 0 && increment.x < 0))
		{
			// Reverse the direction on X axis.
			increment.x = -increment.x;
		}

		if ((sprite.getPosition().y + (size.y / 2) > window.getSize().y && increment.y > 0) ||
			(sprite.getPosition().y - (size.y / 2) < 0 && increment.y < 0))
		{
			increment.y = -increment.y;
		}

		sprite.setPosition(sprite.getPosition() + increment);

		window.clear(sf::Color(16, 16, 16, 255)); // Dark gray.
		window.draw(sprite); // Drawing our sprite.
		window.display();

	}
}