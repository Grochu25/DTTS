#pragma once
#include <sfml/Graphics.hpp>

class Candy : public sf::Sprite
{
private:
	sf::Texture texture;
	bool visibility = false;

public:
	Candy();
	bool isColiding(sf::FloatRect rect);
	bool isVisible();
	void setVisible(bool);
};

