#pragma once

#include <SFML/Graphics.hpp>

enum Direction { RIGHT, FORWARD_RIGHT, FORWARD, FORWARD_LEFT,
	LEFT, BACK_LEFT, BACK, BACK_RIGHT };

class GameCharacter
{
public:
	GameCharacter(const std::string& filename);
	virtual void draw(sf::RenderWindow& window);
	virtual void update() = 0;
	virtual void setPosition(float x, float y);
	virtual void move(sf::Vector2f);
	virtual sf::Vector2f getPosition() const;
	virtual float getHeight() const;
	virtual float getWidth() const;
	virtual void setScale(float scale);
	virtual void kill() = 0;
	virtual bool isActive() = 0;
	virtual bool isDead() = 0;

protected:
	sf::Vector2f velocity;
	int frame_time;
	sf::Clock clock;
	std::vector<sf::IntRect*> movementAnimations[8];
	std::vector<sf::IntRect*> currentAnimation;
	std::vector<sf::IntRect*>::iterator currentFrame;
	Direction direction;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string filename;
	int hp;
};