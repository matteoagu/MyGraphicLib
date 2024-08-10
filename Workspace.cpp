#include "Workspace.h"

void Workspace::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(1000, 700), "My Workspace", sf::Style::Close | sf::Style::Titlebar);
	window->setPosition(sf::Vector2i(0, 0));
	window->setVerticalSyncEnabled(false);
}

void Workspace::initFont()
{
	if (!test_font.loadFromFile("OpenSans-VariableFont_wdth,wght.ttf"))
	{
		throw std::runtime_error{ "Workspace::initFonts() --> FATAL ERROR! Unable to upload the font!\n" };
	}
}

void Workspace::initButtons()
{
	buttons["TEST"] = new agu::Button({200.f, 300.f}, test_font, "Test me!", 100,
		sf::Color(100, 100, 100), sf::Color(150, 150, 150), sf::Color(200, 200, 200),
		sf::Color::White, sf::Color::Yellow, sf::Color::Red,
		10.f, sf::Color::Magenta, sf::Color::Green, sf::Color::Blue);
}

Workspace::Workspace()
{
	initWindow();
	initFont();

	// Initialize the custom objects
	initButtons();
}

Workspace::~Workspace()
{
	delete window;

	// Delete custom objects
	for (auto const& it : buttons) { delete it.second; }
}

void Workspace::updatePollEvents()
{
	while (window->pollEvent(ev))
	{
		// CLOSE
		if (ev.type == sf::Event::Closed) { window->close(); }
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Key::Escape) { window->close(); }
	}
}

void Workspace::updateMousePos()
{
	mouse_pos_view = sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	mouse_pos_view = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}

void Workspace::update()
{
	updatePollEvents();
	updateMousePos();

	// Update custom objects
	for (auto const& it : buttons) { it.second->update(mouse_pos_view); }
}

void Workspace::render()
{
	window->clear();

	// Render custom objects
	for (auto const& it : buttons) { it.second->render(window); }

	window->display();
}

void Workspace::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}
}
