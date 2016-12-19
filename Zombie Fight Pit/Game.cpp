#include "Game.h"

template <typename T1, typename T2>
bool checkCollision(T1* obj1, T2* obj2) {
	sf::Vector2f pos1 = obj1->getPosition();
	sf::Vector2f pos2 = obj2->getPosition();
	if (pos1.x + obj1->getWidth() / 2 >= pos2.x - obj2->getWidth() / 2
		&& pos1.x - obj1->getWidth() / 2 <= pos2.x + obj2->getWidth() / 2
		&& pos1.y + obj1->getHeight() / 2 >= pos2.y - obj2->getHeight() / 2
		&& pos1.y - obj1->getHeight() / 2 <= pos2.y + obj2->getHeight() / 2) {
		obj2->kill();
		return true;
	}
	return false;
}

Game::Game() : window(sf::VideoMode(1200, 800), "Zombie Fight Pit"), score(0), highScore(0),
	arena(sf::Vector2f(600.0f, 600.0f)), zombieHp(3), zombieSpawnInterval(5000), round(1),
	zombieCount(5)
{
	arena.setPosition(300.0f, 100.0f);
	arena.setFillColor(sf::Color::Black);
	arena.setOutlineColor(sf::Color::Red);
	arena.setOutlineThickness(10.0f);
	font.loadFromFile("Crimes Times Six.ttf");
}

Game::Game(Game& rhs) 
{

}

Game::~Game() {}

void Game::run() 
{
	StartMenu startMenu;
	startMenu.run(window);
	while (window.isOpen()) {
		player = new Player();
		player->setPosition(600.0f, 400.0f);
		highScoreText = sf::Text("High Score: " + std::to_string(highScore), font, 50);
		highScoreText.setPosition(480.0f, 20.0f);
		while (window.isOpen() && !player->isDead()) {
			std::thread updates(&Game::update, this);
			render();
			processEvents();
			if (clock.getElapsedTime().asMilliseconds() >= zombieSpawnInterval
				&& zombieCount > 0) {
				std::lock_guard<std::mutex> lock(zombieVectorLock);
				zombies.push_back(new Zombie(zombieHp));
				int x = rand() % 530 + 345;
				int y = rand() % 510 + 145;
				zombies[zombies.size() - 1]->setPosition((float) x, (float) y);
				zombies[zombies.size() - 1]->setTarget(player);
				clock.restart();
				zombieCount--;
			}
			updates.join();
			if (zombieCount == 0 && zombies.size() == 0) {
				advanceRound();
			}
		}
		if (score > highScore) {
			highScore = score;
		}
		delete player;
		zombies.clear();
		clock.restart();
		GameOverMenu gameOver(score, highScore);
		gameOver.run(window);
		score = 0;
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		std::lock_guard<std::mutex> lock(playerLock);
		switch (event.type) {
		case sf::Event::KeyPressed:
			player->handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			player->handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update() 
{
	{
		std::lock_guard<std::mutex> lock(playerLock);
		player->update();
	}
	std::vector<int> zombieRemoves;
	int z = 0;
	std::lock_guard<std::mutex> lock(zombieVectorLock);
	for (Zombie* zombie : zombies) {
		std::lock_guard<std::mutex> lock(playerLock);
		std::vector<Bullet*>& bullets = player->getBullets();
		zombie->update();
		if (player->isActive() && zombie->isActive())
			checkCollision(zombie, player);
		if (zombie->isActive()) {
			std::vector<int> removeIndices;
			int i = 0;
			for (Bullet* bullet : bullets) {
				if (checkCollision(bullet, zombie)) {
					score++;
					removeIndices.push_back(i);
				}
				++i;
			}
			for (int index : removeIndices) {
				bullets.erase(bullets.begin() + index);
			}
		}
		else if (zombie->isDead()) {
			zombieRemoves.push_back(z);
			score += 5;
		}
		++z;
	}
	for (int index : zombieRemoves) {
		zombies.erase(zombies.begin() + index);
	}
}

void Game::render()
{
	window.clear();
	window.draw(arena);
	sf::Text roundText("Round: " + std::to_string(round), font, 50);
	roundText.setPosition(sf::Vector2f(50.0f, 100.0f));
	sf::Text scoreText("Score: " + std::to_string(score), font, 50);
	scoreText.setPosition(sf::Vector2f(940.0f, 100.0f));
	window.draw(roundText);
	window.draw(scoreText);
	window.draw(highScoreText);
	{
		std::lock_guard<std::mutex> lock(playerLock);
		player->draw(window);
	}
	std::lock_guard<std::mutex> lock(zombieVectorLock);
	int z = 0;
	for (Zombie* zombie : zombies) {
		zombie->draw(window);
		++z;
	}
	window.display();
}

void Game::advanceRound() {
	++round;
	zombieHp += 2;
	zombieCount = round * 5;
	if (round < 9) {
		zombieSpawnInterval -= 500;
	}
}