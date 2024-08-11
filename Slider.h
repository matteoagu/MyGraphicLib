#pragma once

#include "states.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <string>

namespace agu
{
	class Slider
	{
	private:
		sf::RectangleShape bar;
		sf::CircleShape circle;

		sf::Vector2f position;
		sf::Vector2f circle_position;

		sf::Text text;
		std::string text_string;
		unsigned char_size;

		sf::Color bar_color;

		sf::Color idle_color;
		sf::Color hoover_color;
		sf::Color active_color;

		sf::Color text_color;
		sf::Color text_outline_color;
		float text_outline_thickness;

		short unsigned status;

		int value;
		bool show_value;

		void initVariables(sf::Vector2f pos, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor, sf::Color barColor,
			float textOutlineThickness, sf::Color textColor, sf::Color textOutlineColor);
		void initText(sf::Font& font);
		void initShapes();

	public:
		Slider(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor, sf::Color barColor,
			float textOutlineThickness, sf::Color textColor, sf::Color textOutlineColor);
		virtual ~Slider();

		bool checkIfAlreadyActive();

		int const getValue() const;
		short int const getStatus() const;

		void const switchShowValue();

		void updateStatus(sf::Vector2f& mousePosView);
		void updateColors();
		void updatePosition(sf::Vector2f& mousePosView);
		void updateValue();
		void updateText();

		void update(sf::Vector2f& mousePosView);
		void render(sf::RenderTarget* target);
	};
}

