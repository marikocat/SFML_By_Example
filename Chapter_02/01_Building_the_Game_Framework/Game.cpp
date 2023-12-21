#include "Game.h"

#include <iostream>

Game::Game() : m_window("Chapter 2", sf::Vector2u(800, 600))
{
	// Setting up class members.
	m_mushroomTexture.loadFromFile("Mushroom.png");
	m_mushroom.setTexture(m_mushroomTexture);
	m_increment = sf::Vector2i(400, 400);
}

Game::~Game()
{
}

void Game::HandleInput()
{

}

void Game::Update()
{
	m_window.Update(); // Update window events.
	//MoveMushroom();
	float frametime = 1.0f / 60.0f;

	if (m_elapsed.asSeconds() >= frametime)
	{
		MoveMushroom();
		m_elapsed -= sf::seconds(frametime);
	}
}

void Game::Render()
{
	m_window.BeginDraw();
	m_window.Draw(m_mushroom);
	m_window.EndDraw();
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
	//m_elapsed = m_clock.restart();
	m_elapsed += m_clock.restart();
}

void Game::MoveMushroom()
{
	sf::Vector2u l_windowSize = m_window.GetWindowSize();
	sf::Vector2u l_textureSize = m_mushroomTexture.getSize();

	if ((m_mushroom.getPosition().x > l_windowSize.x - l_textureSize.x && m_increment.x > 0) ||
		(m_mushroom.getPosition().x < 0 && m_increment.x < 0))
	{
		m_increment.x = -m_increment.x;
	}

	if ((m_mushroom.getPosition().y > l_windowSize.y - l_textureSize.y && m_increment.y > 0) ||
		(m_mushroom.getPosition().y < 0 && m_increment.y < 0))
	{
		m_increment.y = -m_increment.y;
	}

	float fElapsed = m_elapsed.asSeconds();
	std::cout << fElapsed << "\n";

	m_mushroom.setPosition(
		m_mushroom.getPosition().x + (m_increment.x * fElapsed),
		m_mushroom.getPosition().y + (m_increment.y * fElapsed));
}