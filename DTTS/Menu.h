#pragma once
#include "GamePlay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include"Title.h"
#include"Shop.h"


class Menu: public GamePlay
{
	sf::Text candyAmountDisplay;
	sf::Text highScoreDisplay;
	sf::Font font;
	sf::Texture* shopTexture;
	sf::CircleShape shopButton;
	Title* title;
	Shop* shop;

	sf::SoundBuffer buffer;
	sf::Sound buttonSound;

public:
	Menu() {};
	Menu(sf::RenderWindow& window, float cell);
	~Menu();
	void initialScale(float windowX);
	void drawComponents();
	void prepareSounds();
	void start();
	void drawCounters();
};




