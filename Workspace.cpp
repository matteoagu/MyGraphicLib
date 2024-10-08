#include "Workspace.h"

void Workspace::initVariables()
{
	pushing_slider = false;
	pushing_switchbutton = false;
	pushing_box_slider = false;
}

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

void Workspace::initSwitchButtons()
{
	switchButtons["TEST"] = new agu::SwitchButton();
}

void Workspace::initSliders()
{
	sliders["TEST"] = new agu::Slider({ 300.f, 200.f }, test_font, "Test Slider", 50,
		sf::Color::White, sf::Color::Yellow, sf::Color::Red, sf::Color(200, 200, 200),
		3.f, sf::Color::Black, sf::Color::White);
}

void Workspace::initBoxSliders()
{
	boxSliders["TEST"] = new agu::BoxSlider({ 600.f, 500.f }, test_font, "Phase", 40, 
		sf::Color(150, 150, 150), sf::Color::White, sf::Color::White, 4.f, -30.f, 75.f, 0.05f, 3);
}

Workspace::Workspace()
{
	initVariables();
	initWindow();
	initFont();

	// Initialize the custom objects
	initButtons();
	initSwitchButtons();
	initSliders();
	initBoxSliders();
}

Workspace::~Workspace()
{
	delete window;

	// Delete custom objects
	for (auto const& it : buttons) { delete it.second; }
	for (auto const& it : switchButtons) { delete it.second; }
	for (auto const& it : sliders) { delete it.second; }
	for (auto const& it : boxSliders) { delete it.second; }
}

void Workspace::updatePollEvents()
{
	while (window->pollEvent(ev))
	{
		// CLOSE
		if (ev.type == sf::Event::Closed) { window->close(); }
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Key::Escape) { window->close(); }

		// KEYBOARD
		else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Key::Space && keyboard_clock.getElapsedTime().asSeconds() > 0.2f)
		{
			sliders["TEST"]->switchShowValue();
			keyboard_clock.restart();
		}
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

	// Update custom objects and make sure that only one is pushed
	bool pushed = false;
	if (!pushed && !pushing_slider && !pushing_switchbutton && !pushing_box_slider)
	{
		for (auto const& it : buttons) 
		{ 
			it.second->update(mouse_pos_view);
			if (it.second->getStatus() == ACTIVE) { pushed = true; break; }
		}
	}

	if (!pushed && !pushing_slider && !pushing_box_slider)
	{
		for (auto const& it : switchButtons)
		{
			it.second->update(mouse_pos_view);
			if (it.second->isPushed()) { pushed = true; pushing_switchbutton = true; break; }
			else { pushing_switchbutton = false; }
		}
	}

	if (!pushed && !pushing_box_slider)
	{
		for (auto const& it : sliders) 
		{ 
			it.second->update(mouse_pos_view); 
			if (it.second->getStatus() == ButtonStates::ACTIVE) { pushed = true; pushing_slider = true; break; }
			else { pushing_slider = false; }
		}
	}

	if (!pushed)
	{
		for (auto const& it : boxSliders)
		{
			it.second->update(mouse_pos_view);
			if (it.second->getStatus() == ButtonStates::ACTIVE) { pushed = true; pushing_box_slider = true; break; }
			else { pushing_box_slider = false; }
		}
	}
}

void Workspace::render()
{
	window->clear();

	// Render custom objects
	for (auto const& it : buttons) { it.second->render(window); }
	for (auto const& it : switchButtons) { it.second->render(window); }
	for (auto const& it : sliders) { it.second->render(window); }
	for (auto const& it : boxSliders) { it.second->render(window); }

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
