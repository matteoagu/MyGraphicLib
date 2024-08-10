#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>

#include <string>

enum SwitchStatus {ON, OFF};
static sf::Clock SwitchButtonMouseClock;

namespace agu
{
	class SwitchButton
	{
	private:
		sf::RectangleShape left_rect;
		sf::RectangleShape right_rect;

		bool status;

		void initVariables();
		void initShapes();

	public:
		SwitchButton();
		virtual ~SwitchButton();

		bool const getStatus() const;
		bool const isPushed() const;

		void updateStatus(sf::Vector2f& mousePosView);
		void updateColors();

		void update(sf::Vector2f& mousePosView);
		void render(sf::RenderTarget* target);
	};
}
