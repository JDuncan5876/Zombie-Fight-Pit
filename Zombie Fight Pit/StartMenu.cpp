#include "StartMenu.h"

StartMenu::StartMenu() : controlMenu(false)
{
	font.loadFromFile("Crimes Times Six.ttf");
	texts.push_back(new sf::Text("ZOMBIE FIGHT PIT", font, 120));
	texts[0]->setPosition(250.0f, 70.0f);
	options.push_back(new sf::Text("Start", font, 70));
	options[0]->setPosition(510.0f, 280.0f);
	options.push_back(new sf::Text("Controls", font, 70));
	options[1]->setPosition(480.0f, 400.0f);
	options.push_back(new sf::Text("Quit", font, 70));
	options[2]->setPosition(535.0f, 520.0f);
}

void StartMenu::select(sf::RenderWindow& window) {
	if (currentOption == 0) {
		waiting = false;
	}
	else if (currentOption == 2) {
		window.close();
	}
	else {
		controlMenu = !controlMenu;
	}
}

void StartMenu::render(sf::RenderWindow& window) {
	if (!controlMenu) {
		Menu::render(window);
	}
	else {
		window.clear();
		std::string controlString = "";
		controlString += "Movement: WASD\n\n";
		controlString += "Fire: Arrow Keys";
		sf::Text controlText(controlString, font, 70);
		controlText.setPosition(360.0f, 220.0f);
		window.draw(controlText);
		window.display();
	}
}

int StartMenu::run(sf::RenderWindow& window) {
	Menu::run(window);
	waiting = true;
	currentOption = 0;
	while (window.isOpen() && waiting) {
		processEvents(window);
		std::string story = "";
		story += "Well, look who finally woke up!\n";
		story += "How were you surviving out there by yourself?\n";
		story += "I'd be impressed if it weren't so idiotic.\n";
		story += "Here's the deal, I've got a nice little\n";
		story += "community here. So nice, in fact, that they\n";
		story += "sometimes forget about what it's like out there.\n";
		story += "Where they'd be without me to guide them. So I've gotta\n";
		story += "show 'em, you see? Give them a little... entertainment.\n";
		story += "I'm gonna put on a show, and you're the star.";
		sf::Text storyText(story, font, 50);
		storyText.setPosition(70.0f, 50.0f);
		window.clear();
		window.draw(storyText);
		window.display();
	}
	return 0;
}