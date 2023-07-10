#pragma once
#include <SFML/Graphics.hpp>

class Counter : public sf::Text
{
private:
	int score;
	sf::Font font;
	sf::CircleShape disk;

public:
	Counter();
	void setPosition(float x, float y);
	void setCharacterSize(float size);
	void addPoint();
	int getScore();
	sf::CircleShape getDisk();
};