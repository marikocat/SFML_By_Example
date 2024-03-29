#pragma once

#include "GUI_Element.h"

class GUI_Label : public GUI_Element
{
public:
	GUI_Label(const std::string& l_name, GUI_Interface* l_owner);
	~GUI_Label();

	void ReadIn(std::stringstream& l_stream);
	void OnClick(const sf::Vector2f& l_mousePos);
	void OnRelease();
	void OnHover(const sf::Vector2f& l_mousePos);
	void OnLeave();
	void Update(float l_dT);
	void Draw(sf::RenderTarget* l_target);
};