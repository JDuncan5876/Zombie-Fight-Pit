#pragma once
#include "Player.h"
#include <math.h>

#define PI 3.14159265

enum ZombieState { SPAWNING, ZOMBIE_RUNNING, ZOMBIE_DYING, ZOMBIE_DEAD };

class Zombie : public GameCharacter
{
public:
	Zombie(int hp);
	void draw(sf::RenderWindow& window);
	void update();
	void kill();
	void setTarget(Player* target);
	bool isActive();
	bool isDead();
private:
	Player* target;
	ZombieState state;
	std::vector<sf::IntRect*> spawnAnimation;
	std::vector<sf::IntRect*> deathAnimation;
	sf::Texture hitmarkerTexture;
	sf::Sprite hitmarker;
	bool hitFlag;
};

