#pragma once
#include <SFML/Graphics.hpp>

class SkinTile : public sf::Drawable
{
private:
	static sf::Font font;
	sf::RectangleShape background;
	sf::Texture texture;
	sf::Sprite birdSprite;
	sf::Text priceString;
	int price{};
	bool unlocked = false;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	SkinTile(float cell_size = 72, bool enable = false, int price = 100, std::string imgPath = "img/bird.png");

	void setPosition(float x, float y);
	void unlock(bool);
};