#pragma once

#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "EntityManager.h"

#include <iostream>

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
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	SharedContext m_context;
	Window m_window; // The game class holds an instance of our window.
	EntityManager m_entityManager;
	TextureManager m_textureManager;
	StateManager m_stateManager;
};