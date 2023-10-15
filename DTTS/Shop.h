#pragma once
#include "SkinTile.h"
#include "GamePlay.h"

class GamePlay;

class Shop : public GamePlay
{
private:
	sf::RenderWindow* window;
	std::string skinNames[20] = {"bird.png","bird1.png", "bird2.png", "bird3.png", "bird4.png", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
	SkinTile* tiles[20];
	sf::Text candyAmountDisplay;
	sf::Font font;
	sf::RectangleShape upperHalf;
	sf::RectangleShape downHalf;
	sf::RectangleShape bottomRect;
	sf::Texture* returnTexture;
	sf::CircleShape returnButton;
	float cell_size;
	float offset = 0;

public:
	Shop(sf::RenderWindow* window, float cell_size);
	~Shop();
	void moveTiles();
	void open();
	void initialScale();
	void drawCounters();
	void drawComponents();
	void buySkin(int number);

	std::string getSkinPath();
};

