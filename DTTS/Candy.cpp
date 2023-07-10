#include "Candy.h"

Candy::Candy()
{
	texture.loadFromFile("img/candy.png");
	setTexture(texture);
}

bool Candy::isColiding(sf::FloatRect rect)
{
	if (!visibility) return false;

	if (this->getGlobalBounds().intersects(rect))
	{
		visibility = false;
		return true;
	}

	return false;
}

bool Candy::isVisible()
{
	return visibility;
}

void Candy::setVisible(bool visible)
{
	visibility = visible;
}
