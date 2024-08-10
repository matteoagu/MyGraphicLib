#include "Slider.h"

void agu::Slider::initVariables(sf::Vector2f pos, std::string text, unsigned charSize, 
	sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor, sf::Color barColor,
	float textOutlineThickness, sf::Color textColor, sf::Color textOutlineColor)
{
	position = pos;

	text_string = text;
	char_size = charSize;

	idle_color = idleColor;
	hoover_color = hooverColor;
	active_color = activeColor;

	bar_color = barColor;

	text_outline_thickness = textOutlineThickness;
	text_color = textColor;
	text_outline_color = textOutlineColor;

	status = sIDLE;

	value = 50.f;
	show_value = true;
}

void agu::Slider::initText(sf::Font& font)
{
	text.setCharacterSize(char_size);
	text.setFont(font);
	text.setString(text_string + ": " + std::to_string(value));
	text.setFillColor(text_color);
	text.setOutlineThickness(text_outline_thickness);
	text.setOutlineColor(text_outline_color);
	text.setPosition(position);
}

void agu::Slider::initShapes()
{
	bar.setSize(sf::Vector2f(text.getGlobalBounds().width, 10.f));
	bar.setOrigin(bar.getSize() / 2.f);
	bar.setPosition(sf::Vector2f(text.getGlobalBounds().left + text.getGlobalBounds().width / 2.f,
		text.getGlobalBounds().top + text.getGlobalBounds().height * 2.f));
	bar.setFillColor(bar_color);
	circle_position = bar.getPosition();

	circle.setRadius(bar.getSize().y);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	circle.setPosition(circle_position);
	circle.setFillColor(idle_color);
}

agu::Slider::Slider(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize,
	sf::Color idleColor, sf::Color hooverColor, sf::Color activeColor, sf::Color barColor,
	float textOutlineThickness, sf::Color textColor, sf::Color textOutlineColor)
{
	initVariables(pos, text, charSize, 
		idleColor, hooverColor, activeColor, barColor,
		textOutlineThickness, textColor, textOutlineColor);
	initText(font);
	initShapes();
}

agu::Slider::~Slider()
{
}

bool agu::Slider::checkIfAlreadyActive()
{
	return (status == sACTIVE && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

int const agu::Slider::getValue() const
{
	return value;
}

short int const agu::Slider::getStatus() const
{
	return status;
}

void const agu::Slider::switchShowValue()
{
	show_value = !show_value;
}

void agu::Slider::updateStatus(sf::Vector2f& mousePosView)
{
	if (checkIfAlreadyActive()) { status = sACTIVE; }
	else
	{
		float dx = mousePosView.x - circle_position.x;
		float dy = mousePosView.y - circle_position.y;
		float d = sqrt(dx * dx + dy * dy);

		if (d < circle.getRadius())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { status = sACTIVE; }
			else { status = sHOOVER; }
		}

		else { status = sIDLE; }
	}
}

void agu::Slider::updateColors()
{
	switch (status)
	{
	case sIDLE:
		circle.setFillColor(idle_color);
		break;

	case sHOOVER:
		circle.setFillColor(hoover_color);
		break;

	case sACTIVE:
		circle.setFillColor(active_color);
		break;

	default:
		break;
	}
}

void agu::Slider::updatePosition(sf::Vector2f& mousePosView)
{
	if (status == sACTIVE)
	{
		float mx = mousePosView.x;
		if (mx >= bar.getPosition().x + bar.getSize().x / 2.f) { circle_position.x = bar.getPosition().x + bar.getSize().x / 2.f; }
		else if (mx <= bar.getPosition().x - bar.getSize().x / 2.f) { circle_position.x = bar.getPosition().x - bar.getSize().x / 2.f; }
		else { circle_position.x = mx; }

		circle.setPosition(circle_position);
	}
}

void agu::Slider::updateValue()
{
	value = 100 - (bar.getGlobalBounds().left + bar.getSize().x - circle.getPosition().x) * 100 / bar.getSize().x;
}

void agu::Slider::updateText()
{
	if (show_value) { text.setString(text_string + ": " + std::to_string(value)); }
	else { text.setString(text_string); }
}

void agu::Slider::update(sf::Vector2f& mousePosView)
{
	updateStatus(mousePosView);
	updatePosition(mousePosView);
	updateColors();
	updateValue();
	updateText();
}

void agu::Slider::render(sf::RenderTarget* target)
{
	target->draw(bar);
	target->draw(circle);
	target->draw(text);
}
