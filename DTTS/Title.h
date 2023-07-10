#pragma once
#include <SFML/Graphics.hpp>

class Title : public sf::Text
{
private:
	std::string tekst;
	sf::Font font;
	sf::CircleShape disk;

public:
	Title();
	Title(float);
	sf::CircleShape getDisk();
	void setDisk(float x, float y, float size);
};
