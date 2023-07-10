#include "Counter.h"
#include <iostream>

Counter::Counter()
{
	score = 0;
	font.loadFromFile("font/segoeuib.ttf");
	setFont(font);
	setFillColor(sf::Color(0,0,0));
	setString(std::to_string(score));
	disk.setFillColor(sf::Color::White);
}

void Counter::setPosition(float x, float y)
{
	disk.setPosition(x-disk.getRadius(), y - disk.getRadius());
	if(score<10) 
		this->sf::Text::setPosition(disk.getPosition().x+disk.getRadius()-4 + (this->getGlobalBounds().width / 2),
									disk.getPosition().y+disk.getRadius()/2+(this->getGlobalBounds().height/2));
	else
		this->sf::Text::setPosition(disk.getPosition().x + disk.getRadius() - 4 - (this->getGlobalBounds().width/10 ),
			disk.getPosition().y + disk.getRadius() / 2 + (this->getGlobalBounds().height / 2));
}

void Counter::setCharacterSize(float size)
{
	disk.setRadius(size);
	this->sf::Text::setCharacterSize(size);
}

void Counter::addPoint()
{
	score++;
	setString(std::to_string(score));
}

int Counter::getScore()
{
	return score;
}

sf::CircleShape Counter::getDisk()
{
	return disk;
}
