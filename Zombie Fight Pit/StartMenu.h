#pragma once
#include "Menu.h"

class StartMenu : public Menu
{
public:
	StartMenu();
	int run(sf::RenderWindow&);
protected:
	void select(sf::RenderWindow& window);
	void render(sf::RenderWindow& window);
	bool controlMenu;
};

