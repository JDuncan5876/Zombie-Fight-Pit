#include "Zombie.h"

Zombie::Zombie(int hp) : GameCharacter("zombies.png"), state(ZOMBIE_RUNNING), hitFlag(false)
{
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 5, 50, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 70, 50, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 135, 50, 64));
	movementAnimations[FORWARD].push_back(new sf::IntRect(0, 202, 50, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(70, 5, 50, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(70, 70, 50, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(70, 135, 50, 64));
	movementAnimations[FORWARD_LEFT].push_back(new sf::IntRect(70, 202, 50, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(140, 5, 50, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(140, 70, 50, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(140, 135, 50, 64));
	movementAnimations[LEFT].push_back(new sf::IntRect(140, 202, 50, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(210, 5, 50, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(210, 70, 50, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(210, 135, 50, 64));
	movementAnimations[BACK_LEFT].push_back(new sf::IntRect(210, 202, 50, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(280, 5, 50, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(280, 70, 50, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(280, 135, 50, 64));
	movementAnimations[BACK].push_back(new sf::IntRect(280, 202, 50, 64));
	movementAnimations[BACK_RIGHT] = movementAnimations[BACK_LEFT];
	movementAnimations[RIGHT] = movementAnimations[LEFT];
	movementAnimations[FORWARD_RIGHT] = movementAnimations[FORWARD_LEFT];
	spawnAnimation.push_back(new sf::IntRect(740, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(680, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(600, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(540, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(470, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(400, 5, 50, 64));
	spawnAnimation.push_back(new sf::IntRect(330, 5, 50, 64));
	deathAnimation.push_back(new sf::IntRect(330, 135, 50, 64));
	deathAnimation.push_back(new sf::IntRect(400, 135, 50, 64));
	deathAnimation.push_back(new sf::IntRect(470, 135, 50, 64));
	deathAnimation.push_back(new sf::IntRect(535, 135, 50, 64));
	deathAnimation.push_back(new sf::IntRect(595, 135, 50, 64));
	state = SPAWNING;
	currentAnimation = spawnAnimation;
	sprite.setOrigin(sf::Vector2f(25.0f, 32.0f));
	currentFrame = currentAnimation.begin();
	sprite.setTextureRect(**currentFrame);
	frame_time = 125;
	this->hp = hp;
	hitmarkerTexture.loadFromFile("hitmarker.png");
	hitmarker.setTexture(hitmarkerTexture);
	hitmarker.setScale(0.3f, 0.3f);
	clock.restart();
}

void Zombie::draw(sf::RenderWindow& window) {
	GameCharacter::draw(window);
	if (hitFlag) {
		window.draw(hitmarker);
	}
}

void Zombie::update() {
	if (state == ZOMBIE_RUNNING) {
		sf::Vector2f targetPosition = target->getPosition();
		sf::Vector2f zombiePosition = this->getPosition();
		float xdist = targetPosition.x - zombiePosition.x;
		float ydist = targetPosition.y - zombiePosition.y;
		float mag = sqrt(xdist * xdist + ydist * ydist);
		velocity.x = xdist * 0.05f / mag;
		velocity.y = ydist * 0.05f / mag;
		move(velocity);

		float angle = atan2(ydist, xdist);
		Direction prevDir = direction;
		int dir = (int)((angle + 17 * PI / 8) * 4 / PI) % 8;
		direction = static_cast<Direction>(dir);
		if (direction != prevDir) {
			currentAnimation = movementAnimations[direction];
			if (direction == FORWARD_RIGHT || direction == RIGHT || direction == BACK_RIGHT) {
				sprite.setScale(-1.0f, 1.0f);
			}
			else {
				sprite.setScale(1.0f, 1.0f);
			}
			currentFrame = currentAnimation.begin();
		}
	}
	if (clock.getElapsedTime().asMilliseconds() > frame_time) {
		if (currentFrame == currentAnimation.end()) {
			if (state == SPAWNING) {
				currentAnimation = movementAnimations[FORWARD];
				state = ZOMBIE_RUNNING;
			}
			currentFrame = currentAnimation.begin();
			if (state == ZOMBIE_DYING || state == ZOMBIE_DEAD) {
				++(++(++(++currentFrame)));
				state = ZOMBIE_DEAD;
			}
		}
		sprite.setTextureRect(**currentFrame);
		clock.restart();
		++currentFrame;
		if (hitFlag) {
			hitFlag = false;
		}
	}
}

void Zombie::kill() {
	if (--hp <= 0) {
		state = ZOMBIE_DYING;
		currentAnimation = deathAnimation;
		currentFrame = currentAnimation.begin();
	}
	else {
		hitFlag = true;
		sf::Vector2f pos = getPosition();
		hitmarker.setPosition(pos.x - 64.0f, pos.y - 64.0f);
	}
}

void Zombie::setTarget(Player* target) {
	this->target = target;
}

bool Zombie::isActive() {
	return state == ZOMBIE_RUNNING;
}

bool Zombie::isDead() {
	return state == ZOMBIE_DEAD;
}