#include "SwitchButton.h"

void agu::SwitchButton::initVariables()
{
	status = SwitchStates::OFF;
}

void agu::SwitchButton::initShapes()
{
	left_rect.setSize(sf::Vector2f(100.f, 100.f));
	left_rect.setPosition(sf::Vector2f(100.f, 100.f));
	left_rect.setFillColor(sf::Color::Red);
	left_rect.setOutlineThickness(0.f);
	left_rect.setOutlineColor(sf::Color::White);

	right_rect = left_rect;
	right_rect.move(sf::Vector2f(100.f, 0.f));
	right_rect.setFillColor(sf::Color::Green);
}

agu::SwitchButton::SwitchButton()
{
	initVariables();
	initShapes();
}

agu::SwitchButton::~SwitchButton()
{
}

bool const agu::SwitchButton::getStatus() const
{
	return status;
}

bool const agu::SwitchButton::isPushed() const
{
	return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && SwitchButtonMouseClock.restart().asSeconds() < 0.2f);
}

void agu::SwitchButton::updateStatus(sf::Vector2f& mousePosView)
{
	sf::FloatRect buttonBounds = left_rect.getGlobalBounds();

	if (mousePosView.x > buttonBounds.left && mousePosView.x < buttonBounds.left + buttonBounds.width * 2 &&
		mousePosView.y > buttonBounds.top && mousePosView.y < buttonBounds.top + buttonBounds.height &&
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && SwitchButtonMouseClock.restart().asSeconds() > 0.2f)
	{
		status = !status;
	}
}

void agu::SwitchButton::updateColors()
{
	if (status == SwitchStates::ON)
	{
		left_rect.setOutlineThickness(0.f);
		right_rect.setOutlineThickness(5.f);
	}
	else
	{
		left_rect.setOutlineThickness(5.f);
		right_rect.setOutlineThickness(0.f);
	}
}

void agu::SwitchButton::update(sf::Vector2f& mousePosView)
{
	updateStatus(mousePosView);
	updateColors();
}

void agu::SwitchButton::render(sf::RenderTarget* target)
{
	if (status == SwitchStates::OFF)
	{
		target->draw(right_rect);
		target->draw(left_rect);
	}
	else
	{
		target->draw(left_rect);
		target->draw(right_rect);
	}
}
