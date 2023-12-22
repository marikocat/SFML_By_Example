#pragma once

#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

private:
	void MoveSprite(EventDetails* l_details);

	sf::Clock m_clock;

	Window m_window; // The game class holds an instance of our window.

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};