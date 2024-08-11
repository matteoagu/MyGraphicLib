#pragma once

#include "Button.h"
#include "SwitchButton.h"
#include "Slider.h"
#include "BoxSlider.h"

#include <map>
#include <iostream>

class Workspace
{
private:
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Clock keyboard_clock;

	sf::Vector2f mouse_pos;
	sf::Vector2f mouse_pos_view;

	sf::Font test_font;

	// Custom objects
	std::map<std::string, agu::Button*> buttons;
	std::map<std::string, agu::SwitchButton*> switchButtons;
	std::map<std::string, agu::Slider*> sliders;
	std::map<std::string, agu::BoxSlider*> boxSliders;

	bool pushing_switchbutton;
	bool pushing_slider;
	bool pushing_box_slider;

	void initVariables();
	void initWindow();
	void initFont();

	// Initialize the custom objects
	void initButtons();
	void initSwitchButtons();
	void initSliders();
	void initBoxSliders();

public:
	Workspace();
	virtual ~Workspace();

	void updatePollEvents();
	void updateMousePos();

	void update();
	void render();
	void run();
};

