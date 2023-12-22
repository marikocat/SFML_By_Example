#pragma once

#include "Window.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	Window* GetWindow();

	sf::Time GetElapsed();
private:
	sf::Clock m_clock;
	sf::Time m_elapsed;
	void RestartClock();

	SharedContext m_context;
	Window m_window; // The game class holds an instance of our window.
	StateManager m_stateManager;
};