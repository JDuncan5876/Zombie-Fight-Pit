#include "Menu.h"

Menu::Menu() : up(false), down(false), enter(false), pressed(false), currentOption(0), waiting(true)
{
}

int Menu::run(sf::RenderWindow& window) {
	while (waiting && window.isOpen()) {
		processEvents(window);
		render(window);
	}
	return 0;
}

void Menu::processEvents(sf::RenderWindow& window) {
	sf::Event event;
	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			if (!pressed) {
				pressed = true;
				switch (event.key.code) {
				case sf::Keyboard::Up:
					if (currentOption > 0) {
						--currentOption;
					}
					break;
				case sf::Keyboard::Down:
					if (currentOption < options.size() - 1) {
						++currentOption;
					}
					break;
				case sf::Keyboard::Return:
					select(window);
				}
			}
			break;
		case sf::Event::KeyReleased:
			pressed = false;
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Menu::render(sf::RenderWindow& window) {
	window.clear();
	for (sf::Text* text : texts) {
		window.draw(*text);
	}
	sf::RectangleShape selection(sf::Vector2f(355.0f, 120.0f));
	selection.setPosition(420.0f, (**(options.begin() + currentOption)).getPosition().y - 10.0f);
	selection.setFillColor(sf::Color::Black);
	selection.setOutlineColor(sf::Color::White);
	selection.setOutlineThickness(10.0f);
	window.draw(selection);
	for (sf::Text* option : options) {
		window.draw(*option);
	}
	window.display();
}