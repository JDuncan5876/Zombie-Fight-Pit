#include "Player.h"

Player::Player() : GameCharacter("soldier.png"), motionState(STANDING)
{
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 6, 40, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 106, 40, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 172, 40, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 234, 40, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(40, 6, 42, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(40, 106, 42, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(40, 172, 42, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(40, 234, 42, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(86, 4, 32, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(85, 106, 32, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(84, 173, 32, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(83, 235, 32, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(125, 5, 42, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(125, 106, 42, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(125, 173, 42, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(125, 235, 42, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(169, 5, 42, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(170, 106, 42, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(169, 175, 42, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(169, 237, 42, 64));
	movementAnimations[BACK_RIGHT].push_back(new sf::IntRect(215, 5, 42, 64));
	movementAnimations[BACK_RIGHT].push_back(new sf::IntRect(216, 106, 42, 64));
	movementAnimations[BACK_RIGHT].push_back(new sf::IntRect(214, 174, 42, 64));
	movementAnimations[BACK_RIGHT].push_back(new sf::IntRect(213, 236, 42, 64));
	movementAnimations[RIGHT].push_back(new sf::IntRect(270, 6, 42, 64));
	movementAnimations[RIGHT].push_back(new sf::IntRect(270, 106, 42, 64));
	movementAnimations[RIGHT].push_back(new sf::IntRect(269, 175, 42, 64));
	movementAnimations[RIGHT].push_back(new sf::IntRect(267, 237, 42, 64));
	movementAnimations[FORWARD_RIGHT].push_back(new sf::IntRect(325, 6, 42, 64));
	movementAnimations[FORWARD_RIGHT].push_back(new sf::IntRect(324, 106, 42, 64));
	movementAnimations[FORWARD_RIGHT].push_back(new sf::IntRect(323, 174, 42, 64));
	movementAnimations[FORWARD_RIGHT].push_back(new sf::IntRect(321, 236, 42, 64));
	stillFrames[FORWARD].push_back(new sf::IntRect(0, 295, 38, 64));
	stillFrames[FORWARD_LEFT].push_back(new sf::IntRect(40, 297, 42, 64));
	stillFrames[LEFT].push_back(new sf::IntRect(85, 297, 42, 64));
	stillFrames[BACK_LEFT].push_back(new sf::IntRect(125, 297, 42, 64));
	stillFrames[BACK].push_back(new sf::IntRect(170, 297, 42, 64));
	stillFrames[BACK_RIGHT].push_back(new sf::IntRect(215, 297, 42, 64));
	stillFrames[RIGHT].push_back(new sf::IntRect(270, 298, 42, 64));
	stillFrames[FORWARD_RIGHT].push_back(new sf::IntRect(325, 297, 42, 64));
	dyingAnimation.push_back(new sf::IntRect(0, 420, 42, 64));
	dyingAnimation.push_back(new sf::IntRect(50, 420, 42, 64));
	dyingAnimation.push_back(new sf::IntRect(100, 420, 42, 64));
	dyingAnimation.push_back(new sf::IntRect(150, 420, 42, 64));
	dyingAnimation.push_back(new sf::IntRect(200, 420, 42, 64));
	shootingFrame.push_back(new sf::IntRect(55, 360, 24, 64));
	currentAnimation = stillFrames[FORWARD];
	sprite.setOrigin(sf::Vector2f(21.0f, 32.0f));
	velocity.x = 0.0f;
	velocity.y = 0.05f;
	currentFrame = currentAnimation.begin();
	sprite.setTextureRect(**currentFrame);
	frame_time = 125;
	hp = 1000;
	clock.restart();
}

void Player::update() {
	if (motionState != DYING && motionState != SHOOTING && motionState != DEAD) {
		MotionState prevState = motionState;
		Direction prevDir = direction;
		if (keys.w && keys.a) {
			motionState = RUNNING;
			direction = BACK_LEFT;
			velocity.x = -0.0708f;
			velocity.y = -0.0708f;
		}
		else if (keys.a && keys.s) {
			motionState = RUNNING;
			direction = FORWARD_LEFT;
			velocity.x = -0.0708f;
			velocity.y = 0.0708f;
		}
		else if (keys.w && keys.d) {
			motionState = RUNNING;
			direction = BACK_RIGHT;
			velocity.x = 0.0708f;
			velocity.y = -0.0708f;
		}
		else if (keys.d && keys.s) {
			motionState = RUNNING;
			direction = FORWARD_RIGHT;
			velocity.x = 0.0708f;
			velocity.y = 0.0708f;
		}
		else if (keys.w) {
			motionState = RUNNING;
			direction = BACK;
			velocity.x = 0.0f;
			velocity.y = -0.1f;
		}
		else if (keys.a) {
			motionState = RUNNING;
			direction = LEFT;
			velocity.x = -0.1f;
			velocity.y = 0.0f;
		}
		else if (keys.s) {
			motionState = RUNNING;
			direction = FORWARD;
			velocity.x = 0.0f;
			velocity.y = 0.1f;
		}
		else if (keys.d) {
			motionState = RUNNING;
			direction = RIGHT;
			velocity.x = 0.1f;
			velocity.y = 0.0f;
		}
		else {
			motionState = STANDING;
			velocity.x = 0.0f;
			velocity.y = 0.0f;
		}

		if (keys.up || keys.left || keys.down || keys.right) {
			motionState = SHOOTING;
			shotsFired.push_back(new Bullet());
			int lastIndex = shotsFired.size() - 1;
			sf::Vector2f currentPosition = getPosition();
			shotsFired[lastIndex]->setPosition(currentPosition.x, currentPosition.y);
			sf::Vector2f bulletVelocity;
			if (keys.up && keys.right) {
				bulletVelocity.x = 3.54f;
				bulletVelocity.y = -3.54f;
			}
			else if (keys.up && keys.left) {
				bulletVelocity.x = -3.54f;
				bulletVelocity.y = -3.54f;
			}
			else if (keys.down && keys.left) {
				bulletVelocity.x = -3.54f;
				bulletVelocity.y = 3.54f;
			}
			else if (keys.down && keys.right) {
				bulletVelocity.x = 3.54f;
				bulletVelocity.y = 3.54f;
			}
			else if (keys.up) {
				bulletVelocity.x = 0.0f;
				bulletVelocity.y = -5.0f;
			}
			else if (keys.left) {
				bulletVelocity.x = -5.0f;
				bulletVelocity.y = 0.0f;
			}
			else if (keys.down) {
				bulletVelocity.x = 0.0f;
				bulletVelocity.y = 5.0f;
			}
			else {
				bulletVelocity.x = 5.0f;
				bulletVelocity.y = 0.0f;
			}
			shotsFired[lastIndex]->setVelocity(bulletVelocity);
			keys.up = false;
			keys.left = false;
			keys.down = false;
			keys.right = false;
		}

		if (motionState != prevState) {
			if (motionState == STANDING) {
				currentAnimation = stillFrames[direction];
			}
			else if (motionState == RUNNING) {
				currentAnimation = movementAnimations[direction];
			}
			else {
				currentAnimation = shootingFrame;
			}
			currentFrame = currentAnimation.begin();
		}
		else if (prevDir != direction) {
			currentAnimation = movementAnimations[direction];
			currentFrame = currentAnimation.begin();
		}

		move(velocity);
	}
	if (clock.getElapsedTime().asMilliseconds() > frame_time) {
		if (currentFrame == currentAnimation.end()) {
			currentFrame = currentAnimation.begin();
			if (motionState == DYING || motionState == DEAD) {
				++(++(++(++currentFrame)));
				motionState = DEAD;
			}
			if (motionState == SHOOTING) {
				motionState = STANDING;
				currentAnimation = stillFrames[direction];
				currentFrame = currentAnimation.begin();
			}
		}
		sprite.setTextureRect(**currentFrame);
		clock.restart();
		++currentFrame;
	}
	std::vector<int> removeIndices;
	int i = 0;
	for (Bullet* bullet : shotsFired) {
		bullet->move();
		sf::Vector2f pos = bullet->getPosition();
		if (pos.x > 1200 || pos.x < 0 || pos.y > 800 || pos.y < 0) {
			removeIndices.push_back(i);
		}
		++i;
	}
	for (int index : removeIndices) {
		shotsFired.erase(shotsFired.begin() + index);
	}
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isDown) {
	switch (key) {
	case sf::Keyboard::W:
		keys.w = isDown;
		break;
	case sf::Keyboard::A:
		keys.a = isDown;
		break;
	case sf::Keyboard::S:
		keys.s = isDown;
		break;
	case sf::Keyboard::D:
		keys.d = isDown;
		break;
	case sf::Keyboard::Up:
		keys.up = isDown;
		break;
	case sf::Keyboard::Left:
		keys.left = isDown;
		break;
	case sf::Keyboard::Right:
		keys.right = isDown;
		break;
	case sf::Keyboard::Down:
		keys.down = isDown;
		break;
	}
}

void Player::kill() {
	if (--hp <= 0) {
		motionState = DYING;
		currentAnimation = dyingAnimation;
		currentFrame = currentAnimation.begin();
	}
}

bool Player::isActive() {
	return motionState != DYING && motionState != DEAD;
}

bool Player::isDead() {
	return motionState == DEAD;
}

std::vector<Bullet*>& Player::getBullets() {
	return shotsFired;
}