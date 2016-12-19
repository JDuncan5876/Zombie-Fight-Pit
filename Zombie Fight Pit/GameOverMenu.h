#pragma once
#include "Menu.h"
class GameOverMenu : public Menu
{
public:
	GameOverMenu(int score, int highScore);
protected:
	void select(sf::RenderWindow&);
};

