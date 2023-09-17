#include "skinTile.h"
#include <iostream>

sf::Font SkinTile::font;

SkinTile::SkinTile(float cell_size, bool enable, int price, std::string imgPath)
{
	this->price = price;
	this->unlocked = enable;

	background.setFillColor(sf::Color(180,180,180));
	background.setSize(sf::Vector2f(cell_size*3,cell_size*1.2));
	texture.loadFromFile(imgPath);
	birdSprite.setTexture(texture);
	birdSprite.setScale(cell_size*1.2/290,cell_size*1.2/290);
	birdSprite.setOrigin(birdSprite.getGlobalBounds().width/2, birdSprite.getGlobalBounds().height/2);

	font.loadFromFile("font/ariblk.ttf");
	priceString.setFont(font);
	priceString.setFillColor(sf::Color(255, 110, 38));
	priceString.setString(std::to_string(price));
	priceString.setScale(cell_size / 40, cell_size / 40);
}

void SkinTile::unlock(bool state)
{
	unlocked = state;
}

void SkinTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(background);
	if (unlocked)
		target.draw(birdSprite);
	else
		target.draw(priceString);
}

void SkinTile::setPosition(float x, float y)
{
	background.setPosition(x, y);
	birdSprite.setPosition(x + (background.getGlobalBounds().width / 2) - birdSprite.getGlobalBounds().width/2.5,
		y + (background.getGlobalBounds().height / 2) - birdSprite.getGlobalBounds().height/2.5);
	priceString.setPosition(x + (background.getGlobalBounds().width / 2) - priceString.getGlobalBounds().width/2,
		y + (background.getGlobalBounds().height / 2) - priceString.getGlobalBounds().height/1.25);
}
