#pragma once

#include "GameCharacter.h"
#include "Bullet.h"

enum MotionState { STANDING, RUNNING, SHOOTING, DYING, DEAD };

class Player : public GameCharacter
{
public:
	Player();
	void update();
	void handlePlayerInput(sf::Keyboard::Key key, bool isDown);
	void kill();
	bool isActive();
	bool isDead();
	std::vector<Bullet*>& getBullets();

private:
	MotionState motionState;
	struct {
		bool w = false;
		bool a = false;
		bool s = false;
		bool d = false;
		bool up = false;
		bool left = false;
		bool right = false;
		bool down = false;
	} keys;
	std::vector<sf::IntRect*> stillFrames[8];
	std::vector<sf::IntRect*> dyingAnimation;
	std::vector<sf::IntRect*> shootingFrame;
	std::vector<Bullet*> shotsFired;
};

