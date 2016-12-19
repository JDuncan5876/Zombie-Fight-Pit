#include "Bullet.h"

Bullet::Bullet()
{
}

void Bullet::setPosition(float x, float y) {
	position = sf::Vector2f(x, y);
}

void Bullet:: move() {
	position += velocity;
}

sf::Vector2f Bullet::getPosition() const {
	return position;
}

float Bullet::getWidth() const {
	return 5.0f;
}

float Bullet::getHeight() const {
	return 5.0f;
}

void Bullet::setVelocity(sf::Vector2f velocity) {
	this->velocity = velocity;
}