#include "Bird.h"

sf::Image Bird::createBirdDown(std::string imgPath)
{
	sf::Image file, finalImage;
	file.loadFromFile(imgPath);
	finalImage.create(340, 240);
	finalImage.copy(file, 0, 0, sf::IntRect(0, 0, 340, 240));
	finalImage.copy(file, 100, 120, sf::IntRect(340, 0, 100, 90), true);
	return finalImage;
}

sf::Image Bird::createBirdUp(std::string imgPath)
{
	sf::Image file, finalImage;
	file.loadFromFile(imgPath);
	finalImage.create(340, 240);
	finalImage.copy(file, 0, 0, sf::IntRect(0, 0, 340, 240));
	file.flipVertically();
	finalImage.copy(file, 100, 40, sf::IntRect(340, 140, 100, 90), true);
	return finalImage;
}

Bird::Bird() :Bird("img/skins/bird.png") {}

Bird::Bird(std::string texturePath)
{
	direction = RIGHT;
	verticalSpeed = 0;
	horizontalSpeed = 10;
	texture1.loadFromImage(Bird::createBirdDown(texturePath));
	texture2.loadFromImage(Bird::createBirdUp(texturePath));
	this->setTexture(texture1);
	prepareSounds();
}

void Bird::prepareSounds()
{
	jumpSoundBuffer.loadFromFile("audio/jump.wav");
	deathSoundBuffer.loadFromFile("audio/dead.wav");
	pointSoundBuffer.loadFromFile("audio/point.wav");
	jumpSound.setBuffer(jumpSoundBuffer);
	deathSound.setBuffer(deathSoundBuffer);
	pointSound.setBuffer(pointSoundBuffer);
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

	if(alive)
		pointSound.play();
}

void Bird::toss()
{
	this->setTexture(texture2);
	verticalSpeed = -15;
	if (alive)
		jumpSound.play();
}

void Bird::kill()
{
	if (alive)
		deathSound.play();
	texture1.loadFromFile("img/bird_dead.png");
	alive = false;
}

void Bird::setVerticalSpeed(float speed)
{
	verticalSpeed = speed;
}

void Bird::setNewTextures(std::string imgPath)
{
	texture1.loadFromImage(Bird::createBirdDown(imgPath));
	texture2.loadFromImage(Bird::createBirdUp(imgPath));
}

int Bird::getDirection()
{
	return static_cast<int>(direction);
}

bool Bird::isAlive()
{
	return alive;
}