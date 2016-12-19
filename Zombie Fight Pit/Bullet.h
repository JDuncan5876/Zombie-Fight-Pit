#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet();
	void setPosition(float x, float y);
	void move();
	sf::Vector2f getPosition() const;
	float getWidth() const;
	float getHeight() const;
	void setVelocity(sf::Vector2f);
private:
	sf::Vector2f velocity;
	sf::Vector2f position;
};

