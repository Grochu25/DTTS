#pragma once
#include <sfml/Graphics.hpp>


class Bird : public sf::Sprite
{
private:
	enum direction {LEFT, RIGHT};

	direction direction;
	int verticalSpeed = 0;
	float horizontalSpeed;
	bool alive = true;
	sf::Texture texture1;
	sf::Texture texture2;

public:
	Bird();
	Bird(std::string texturePath1, std::string texturePath2);

	void move();
	void move(float,float);
	void bounce();
	void toss();
	void kill();
	void setVerticalSpeed(float);
	
	int getDirection();
	bool isAlive();
};

