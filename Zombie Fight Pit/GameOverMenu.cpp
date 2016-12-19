#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(int score, int highScore)
{
	font.loadFromFile("Crimes Times Six.ttf");
	texts.push_back(new sf::Text("GAME OVER", font, 100));
	texts[0]->setPosition(395.0f, 70.0f);
	texts.push_back(new sf::Text("Score " + std::to_string(score), font, 50));
	texts[1]->setPosition(515.0f, 250.0f);
	texts.push_back(new sf::Text("High Score " + std::to_string(highScore), font, 50));
	texts[2]->setPosition(470.0f, 310.0f);
	options.push_back(new sf::Text("Play Again", font, 70));
	options[0]->setPosition(455.0f, 450.0f);
	options.push_back(new sf::Text("Quit", font, 70));
	options[1]->setPosition(540.0f, 600.0f);
}

void GameOverMenu::select(sf::RenderWindow& window) {
	if (currentOption == 0) {
		waiting = false;
	}
	else {
		window.close();
	}
}