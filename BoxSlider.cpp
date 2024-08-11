#include "BoxSlider.h"


void agu::BoxSlider::initVariables(sf::Vector2f pos, std::string text, unsigned charSize, 
	sf::Color color, sf::Color outlineColor, sf::Color textColor, 
	float outlineThikness, float minVal, float maxVal, float sens, int approx)
{
	position = pos;

	text_string = text;
	char_size = charSize;

	this->color = color;
	text_color = textColor;
	outline_color = outlineColor;

	outline_thickness = outlineThikness;
	status = ButtonStates::IDLE;

	min_val = minVal;
	max_val = maxVal;
	value = (max_val - min_val) / 2.f;
	sensitivity = sens;
	this->approx = approx;
}

void agu::BoxSlider::initText(sf::Font& font)
{
	text.setCharacterSize(char_size);
	text.setFont(font);
	updateText();
	text.setFillColor(text_color);
	text.setPosition(position);
}

void agu::BoxSlider::initShapes()
{
	box.setPosition(text.getPosition());
	box.setSize(sf::Vector2f(text.getGlobalBounds().width * 1.1f, text.getGlobalBounds().height * 2.f));
	box.setOutlineThickness(outline_thickness);
	box.setFillColor(color);
	box.setOutlineColor(outline_color);
}

agu::BoxSlider::BoxSlider(sf::Vector2f pos, sf::Font& font, std::string text, unsigned charSize, 
	sf::Color color, sf::Color outlineColor, sf::Color textColor, 
	float outlineThikness, float minVal, float maxVal, float sens, int approx)
{
	initVariables(pos, text, charSize, color, outlineColor, textColor, outlineThikness, minVal, maxVal, sens, approx);
	initText(font);
	initShapes();
}

agu::BoxSlider::~BoxSlider()
{
}

bool agu::BoxSlider::checkIfAlreadyActive()
{
	return (status == ButtonStates::ACTIVE && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
}

float const agu::BoxSlider::getValue() const
{
	return value;
}

short int const agu::BoxSlider::getStatus() const
{
	return status;
}

void agu::BoxSlider::updateStatus(sf::Vector2f& mousePosView)
{
	if (checkIfAlreadyActive()) { status = ButtonStates::ACTIVE; }
	else
	{
		sf::FloatRect button_bounds = box.getGlobalBounds();

		if (mousePosView.x > button_bounds.left && mousePosView.x<button_bounds.left + button_bounds.width &&
			mousePosView.y>button_bounds.top && mousePosView.y < button_bounds.top + button_bounds.height)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) { status = ButtonStates::ACTIVE; }
			else { status = ButtonStates::HOOVER; previous_mouse_x = NULL; }
		}

		else { status = ButtonStates::IDLE; previous_mouse_x = NULL; }
	}
}

void agu::BoxSlider::updateValue(sf::Vector2f& mousePosView)
{
	if (status == ButtonStates::ACTIVE)
	{
		float mx = mousePosView.x;
		if (previous_mouse_x != NULL)
		{
			float new_value = value + (mx - previous_mouse_x) * sensitivity;

			if (new_value >= max_val) { value = max_val; }
			else if (new_value <= min_val) { value = min_val; }
			else { value = new_value; }
		}

		previous_mouse_x = mx;
	}
}

void agu::BoxSlider::updateText()
{
	std::ostringstream out;
	out << std::fixed << std::setprecision(approx) << value;
	text.setString(text_string + ": " + out.str());
}

void agu::BoxSlider::updateColor()
{
	if (value == min_val) { text.setFillColor(sf::Color::Green); }
	else if (value == max_val) { text.setFillColor(sf::Color::Red); }
	else { text.setFillColor(text_color); }
}

void agu::BoxSlider::update(sf::Vector2f& mousePosView)
{
	updateStatus(mousePosView);
	updateValue(mousePosView);
	updateText();
	updateColor();
}

void agu::BoxSlider::render(sf::RenderTarget* target)
{
	target->draw(box);
	target->draw(text);
}
