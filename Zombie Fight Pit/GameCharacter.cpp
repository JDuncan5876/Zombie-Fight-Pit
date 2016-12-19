#include "GameCharacter.h"

GameCharacter::GameCharacter(const std::string& filename) : filename(filename), direction(FORWARD)
{
	texture.loadFromFile(filename);
	sprite.setTexture(texture);
	velocity.x = 0.0f;
	velocity.y = 0.0f;
}

void GameCharacter::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}

void GameCharacter::move(sf::Vector2f loc) {
	sf::Vector2f newPosition = getPosition() + loc;
	if (newPosition.x > 345.0f && newPosition.x < 865.0f
		&& newPosition.y > 145.0f && newPosition.y < 665.0f)
		sprite.move(loc);
}

void GameCharacter::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

sf::Vector2f GameCharacter::getPosition() const {
	return sprite.getPosition();
}

float GameCharacter::getHeight() const {
	return sprite.getLocalBounds().height;
}

float GameCharacter::getWidth() const {
	return sprite.getLocalBounds().width;
}

void GameCharacter::setScale(float scale) {
	sprite.setScale(scale, scale);
}