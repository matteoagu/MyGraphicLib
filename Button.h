#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <string>

enum ButtonStates { IDLE, HOOVER, ACTIVE };
static sf::Clock mouseClock;

namespace agu
{
	class Button
	{
	private:
		sf::RectangleShape rect;
		sf::Vector2f position;

		sf::Text text;
		std::string text_string;
		unsigned char_size;

		sf::Color idle_color;
		sf::Color hoover_color;
		sf::Color active_color;

		sf::Color text_idle_color;
		sf::Color text_hoover_color;
		sf::Color text_active_color;

		float text_outline_thickness;
		sf::Color text_outline_idle_color;
		sf::Color text_outline_hoover_color;
		sf::Color text_outline_active_color;


		short unsigned status;

		void initVariables(sf::Vector2f pos, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor,
			sf::Color textIdleColor, sf::Color textHooverColor, sf::Color textActiveColor,
			float textOutlineThikness,
			sf::Color textOutlineIdleColor, sf::Color textOutlineHooverColor, sf::Color textOutlineActiveColor);
		void initText(sf::Font& font);
		void initShape();

	public:
		Button(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize,
			sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor,
			sf::Color textIdleColor, sf::Color textHooverColor, sf::Color textActiveColor,
			float textOutlineThikness, sf::Color textOutlineIdleColor, sf::Color textOutlineHooverColor, sf::Color textOutlineActiveColor);
		virtual ~Button();

		// Get functions
		short unsigned const getStatus() const;

		bool checkIfAlreadyActive();

		// Update functions
		void updateStatus(sf::Vector2f& mouse_pos_view);
		void updateColors();

		void update(sf::Vector2f& mouse_pos_view);
		void render(sf::RenderTarget* target);
	};
}