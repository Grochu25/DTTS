#include "Bird.h"

Bird::Bird() :Bird("img/bird.png", "img/bird_2.png") {}

Bird::Bird(std::string texturePath1, std::string texturePath2)
{
	direction = RIGHT;
	verticalSpeed = 0;
	horizontalSpeed = 10;
	texture1.loadFromFile(texturePath1);
	texture2.loadFromFile(texturePath2);
	this->setTexture(texture1);
}

void Bird::move()
{
	if (direction == LEFT)
		this->sf::Sprite::move(-horizontalSpeed, verticalSpeed);
	else if (direction == RIGHT)
		this->sf::Sprite::move(horizontalSpeed, verticalSpeed);
	verticalSpeed += 1.25;

	if (verticalSpeed > 0)
		this->setTexture(texture1);
}

void Bird::move(float x, float y)
{
	sf::Sprite::move(x, y);
}

void Bird::bounce()
{
	if (direction == LEFT)
	{
		direction = RIGHT;
		scale(-1, 1);
		setOrigin(0, 0);
	}
	else if (direction == RIGHT)
	{
		direction = LEFT;
		scale(-1, 1);
		setOrigin(240,0);
	}
	horizontalSpeed += 0.125;
}

void Bird::toss()
{
	this->setTexture(texture2);
	verticalSpeed = -15;
}

void Bird::kill()
{
	texture1.loadFromFile("img/bird_dead.png");
	alive = false;
}

void Bird::setVerticalSpeed(float speed)
{
	verticalSpeed = speed;
}

int Bird::getDirection()
{
	return static_cast<int>(direction);
}

bool Bird::isAlive()
{
	return alive;
}