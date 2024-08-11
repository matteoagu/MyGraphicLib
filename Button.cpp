#include "Button.h"

void agu::Button::initVariables(sf::Vector2f pos, std::string text, unsigned charSize,
	sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor,
	sf::Color textIdleColor, sf::Color textHooverColor, sf::Color textActiveColor,
	float textOutlineThikness,
	sf::Color textOutlineIdleColor, sf::Color textOutlineHooverColor, sf::Color textOutlineActiveColor)
{
	position = pos;

	text_string = text;
	char_size = charSize;

	idle_color = idleColor;
	hoover_color = hooverColor;
	active_color = activeColor;

	text_idle_color = textIdleColor;
	text_hoover_color = textHooverColor;
	text_active_color = textActiveColor;

	text_outline_thickness = textOutlineThikness;
	text_outline_idle_color = textOutlineIdleColor;
	text_outline_hoover_color = textOutlineHooverColor;
	text_outline_active_color = textOutlineActiveColor;

	status = IDLE;
}

void agu::Button::initText(sf::Font& font)
{
	text.setCharacterSize(char_size);
	text.setFont(font);
	text.setString(text_string);
	text.setFillColor(text_idle_color);
	text.setOutlineThickness(text_outline_thickness);
	text.setOutlineColor(text_outline_idle_color);
	text.setPosition(position);
}

void agu::Button::initShape()
{
	rect.setPosition(text.getPosition());
	rect.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height * 1.5f));
	rect.setFillColor(idle_color);
}

agu::Button::Button(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize,
	sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor,
	sf::Color textIdleColor, sf::Color textHooverColor, sf::Color textActiveColor,
	float textOutlineThikness,
	sf::Color textOutlineIdleColor, sf::Color textOutlineHooverColor, sf::Color textOutlineActiveColor)
{
	initVariables(pos, text, charSize, 
		idleColor, hooverColor, activeColor, 
		textIdleColor, textHooverColor, textActiveColor,
		textOutlineThikness, textOutlineIdleColor, textOutlineHooverColor, textOutlineActiveColor);
	initText(font);
	initShape();
}

agu::Button::~Button()
{
}

short unsigned const agu::Button::getStatus()
{
	return status;
}

sf::Vector2f const agu::Button::getPosition()
{
	return position;
}

void agu::Button::setPosition(sf::Vector2f pos)
{
	position = pos;
}

bool agu::Button::checkIfAlreadyActive()
{
	return (status == ButtonStates::ACTIVE && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

void agu::Button::updateStatus(sf::Vector2f& mouse_pos_view)
{
	if (checkIfAlreadyActive()) { status = ButtonStates::ACTIVE; }
	else
	{
		sf::FloatRect button_bounds = rect.getGlobalBounds();

		if (mouse_pos_view.x > button_bounds.left && mouse_pos_view.x<button_bounds.left + button_bounds.width &&
			mouse_pos_view.y>button_bounds.top && mouse_pos_view.y < button_bounds.top + button_bounds.height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && ButtonMouseClock.getElapsedTime().asSeconds() > 0.2f)
			{
				status = ButtonStates::ACTIVE;
				ButtonMouseClock.restart();
			}

			else { status = ButtonStates::HOOVER; }
		}

		else { status = ButtonStates::IDLE; }
	}
}

void agu::Button::updateColors()
{
	switch (status)
	{
	case ButtonStates::IDLE:
		rect.setFillColor(idle_color);
		text.setFillColor(text_idle_color);
		text.setOutlineColor(text_outline_idle_color);
		break;

	case ButtonStates::HOOVER:
		rect.setFillColor(hoover_color);
		text.setFillColor(text_hoover_color);
		text.setOutlineColor(text_outline_hoover_color);
		break;

	case ButtonStates::ACTIVE:
		rect.setFillColor(active_color);
		text.setFillColor(text_active_color);
		text.setOutlineColor(text_outline_active_color);
		break;

	default:
		break;
	}
}

void agu::Button::update(sf::Vector2f& mouse_pos_view)
{
	updateStatus(mouse_pos_view);
	updateColors();
}

void agu::Button::render(sf::RenderTarget* target)
{
	target->draw(rect);
	target->draw(text);
}
