#pragma once

#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	Window* GetWindow();

	sf::Time GetElapsed();
	void RestartClock();

private:
	void MoveMushroom();

	sf::Clock m_clock;
	sf::Time m_elapsed;

	Window m_window; // The game class holds an instance of our window.

	sf::Texture m_mushroomTexture;
	sf::Sprite m_mushroom;
	sf::Vector2i m_increment;
};