#pragma once
#include "GamePlay.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include"Title.h"


class Menu: public GamePlay
{
	sf::Text candyAmountDisplay;
	sf::Text highScoreDisplay;
	sf::Text rulesText;
	sf::Font font;
	Title* title;

public:
	Menu(sf::RenderWindow& window, float cell);
	~Menu();
	void drawComponents();
	void start();
	void drawCounters();
};




