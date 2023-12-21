#pragma once

#include "Window.h"
#include "World.h"
#include "Textbox.h"

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
	sf::Clock m_clock;
	float m_elapsed;

	Window m_window; // The game class holds an instance of our window.

	World m_world;
	Snake m_snake;
	Textbox m_textbox;
};