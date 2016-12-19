#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"
#include "StartMenu.h"
#include "GameOverMenu.h"

class Game {
public:
	//use default screen size
	Game();
	Game(Game&);
	~Game();
	//run the game
	void run();

private:
	void processEvents();
	//update the game objects
	void update();
	//draw the scene
	void render();
	void advanceRound();

	sf::RenderWindow window;
	Player* player;
	std::vector<Zombie*> zombies;
	sf::Clock clock;
	int score;
	int highScore;
	sf::RectangleShape arena;
	int zombieHp;
	int zombieSpawnInterval;
	int round;
	int zombieCount;
	std::mutex playerLock;
	std::mutex zombieVectorLock;
	sf::Font font;
	sf::Text highScoreText;
};
