#pragma once

#include <string>

#include <SFML/Graphics.hpp>

#include "EventManager.h"

class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw(); // Clear the window.
	void EndDraw(); // Display the changes.

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool isFocused();

	void ToggleFullscreen(EventDetails* l_details);
	void Close(EventDetails* l_details = nullptr);

	EventManager* GetEventManager();

	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();
private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();

	EventManager m_eventManager;

	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	bool m_isFocused;
};