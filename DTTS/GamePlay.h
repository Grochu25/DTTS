#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <random>
#include <ctime>
#include <fstream>
#include <iostream>
#include "Bird.h"
#include "Spikes.h"
#include "Counter.h"
#include "Candy.h"

class GamePlay
{
protected:
	float cell_size{};
	int highScore{};
	int candyAmount{};
	bool gameOver = false;
	Bird bird;
	float coordinateY;
	Counter counter;
	Spikes spikeController;
	Candy candy;
	sf::RenderWindow* window = nullptr;
	sf::RectangleShape background;
	bool *boughtSkins;
	std::string actualSkinName = "img/skins/bird.png";

public:
	GamePlay() {}
	GamePlay(sf::RenderWindow &window, float cell);
	void readDataFile();
	void initialScale();
	void drawComponents();
	void changeColor();
	void placeCandy();
	void moveBird();
	void start();

	friend void writeDataFile(GamePlay*);
};

