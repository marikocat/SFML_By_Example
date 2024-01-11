#include "Game.h"

#include <iostream>

Game::Game() : m_window("Chapter 7", sf::Vector2u(800, 600)), 
	m_stateManager(&m_context), m_entityManager(&m_context, 100)
{
	m_clock.restart();
	srand(time(NULL));
	
	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_context.m_textureManager = &m_textureManager;
	m_context.m_entityManager = &m_entityManager;

	m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game() {}

void Game::Update()
{
	m_window.Update(); // Update window events.
	m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
	m_window.BeginDraw();

	// Render.
	m_stateManager.Draw();
	// Debug.
	if (m_context.m_debugOverlay.Debug())
	{
		m_context.m_debugOverlay.Draw(m_window.GetRenderWindow());
	}
	// End debug.

	m_window.EndDraw();
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

Window* Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart();
}