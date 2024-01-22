#pragma once

#include <iostream>

#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "TextureManager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Window* GetWindow();
private:
	void RestartClock();

	sf::Clock m_clock;
	sf::Time m_elapsed;
	SharedContext m_context;
	Window m_window;
	TextureManager m_textureManager;
	FontManager m_fontManager;
	SystemManager m_systemManager;
	EntityManager m_entityManager;
	GUI_Manager m_guiManager;
	StateManager m_stateManager;
};