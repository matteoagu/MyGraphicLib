#pragma once

#include "states.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>

namespace agu
{
	class BoxSlider
	{
	private:
		sf::RectangleShape box;
		sf::Vector2f position;
		sf::Color color;
		sf::Color outline_color;
		float outline_thickness;

		sf::Text text;
		std::string text_string;
		unsigned char_size;
		sf::Color text_color;

		short unsigned status;
		float sensitivity;
		float previous_mouse_x;

		float value;
		float min_val;
		float max_val;
		int approx;

		void initVariables(sf::Vector2f pos, std::string text, unsigned charSize,
			sf::Color color, sf::Color outlineColor, sf::Color textColor, 
			float outlineThikness, float minVal, float maxVal, float sens, int approx);
		void initText(sf::Font& font);
		void initShapes();

	public:
		BoxSlider(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize,
			sf::Color color, sf::Color outlineColor, sf::Color textColor,
			float outlineThikness, float minVal, float maxVal, float sens, int approx = 0);
		virtual ~BoxSlider();

		bool checkIfAlreadyActive();

		float const getValue() const;
		short int const getStatus() const;

		void updateStatus(sf::Vector2f& mousePosView);
		void updateValue(sf::Vector2f& mousePosView);
		void updateText();
		void updateColor();

		void update(sf::Vector2f& mousePosView);
		void render(sf::RenderTarget* target);
	};
}

