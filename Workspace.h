#pragma once

#include "Button.h"

#include <map>
#include <iostream>

class Workspace
{
private:
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Vector2f mouse_pos;
	sf::Vector2f mouse_pos_view;

	sf::Font test_font;

	std::map<std::string, agu::Button*> buttons;

	void initWindow();
	void initFont();

	// Initialize the custom objects
	void initButtons();

public:
	Workspace();
	virtual ~Workspace();

	void updatePollEvents();
	void updateMousePos();

	void update();
	void render();
	void run();
};

