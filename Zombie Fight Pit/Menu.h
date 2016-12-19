#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
	Menu();
	virtual int run(sf::RenderWindow&);
protected:
	virtual void select(sf::RenderWindow&) = 0;
	void processEvents(sf::RenderWindow&);
	virtual void render(sf::RenderWindow&);
	sf::Font font;
	std::vector<sf::Text*> texts;
	std::vector<sf::Text*> options;
	int currentOption;
	bool up;
	bool down;
	bool enter;
	bool pressed;
	bool waiting;
};

