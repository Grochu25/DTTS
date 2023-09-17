#include "Shop.h"

Shop::Shop(sf::RenderWindow* window, float cell_size)
{
	this->window = window;
	this->cell_size = cell_size;

	readDataFile();
	initialScale();
	drawCounters();

	for (int i = 0; i < 20; i++)
	{
		if (skinNames[i] != "")
			tiles[i] = new SkinTile(cell_size, boughtSkins[i], 100, "img/skins/" + skinNames[i]);
		else
			tiles[i] = new SkinTile(cell_size, boughtSkins[i], 100, "img/bird.png");
	}
	moveTiles();
}

void Shop::initialScale()
{
	background.setPosition(cell_size / 2, cell_size / 2);
	background.setSize(sf::Vector2f(cell_size * 8, cell_size * 13));
	background.setOutlineThickness(cell_size / 2);
	background.setOutlineColor(sf::Color(166, 166, 166));
	background.setFillColor(sf::Color(120, 120, 120));

	upperHalf.setSize(sf::Vector2f(cell_size*9,cell_size/2));
	upperHalf.setFillColor(sf::Color(166, 166, 166));

	downHalf.setSize(sf::Vector2f(cell_size * 8, cell_size*2));
	downHalf.setFillColor(sf::Color(120, 120, 120));
	downHalf.setPosition(cell_size / 2, cell_size / 2);

	bottomRect.setSize(sf::Vector2f(cell_size * 9, cell_size / 2));
	bottomRect.setFillColor(sf::Color(166, 166, 166));
	bottomRect.setPosition(sf::Vector2f(0, cell_size*13.5));

	spikeController.setColor(sf::Color(166, 166, 166));
	spikeController.setCellSize(cell_size);
	spikeController.placeSpikesTB();

	candy.scale(cell_size / 240, cell_size / 240);
	candy.setPosition(sf::Vector2f(cell_size*5,cell_size*1.5));

	returnTexture = new sf::Texture();
	returnTexture->loadFromFile("img/return.png");
	returnButton.setTexture(returnTexture);
	returnButton.setRadius(cell_size * 0.6);
	returnButton.setPosition(cell_size*1.5, cell_size*1.25);
}

void Shop::moveTiles()
{
	if (offset > 0) offset = 0;
	if (offset < -2* 16) offset = -2 * 16;
	for (int j = 0; j < 10; j++)
		for (int i = 0; i < 2; i++)
		{
			tiles[j+i*10]->setPosition(cell_size + cell_size * 4 * i, cell_size * 3 + cell_size*1.5 * j + (cell_size*0.15)*offset);
		}
}

void Shop::drawCounters()
{
	font.loadFromFile("font/ariblk.ttf");
	candyAmountDisplay.setFont(font);
	candyAmountDisplay.setFillColor(sf::Color(255, 110, 38));
	candyAmountDisplay.setString(std::to_string(candyAmount));
	candyAmountDisplay.setScale(cell_size / 40, cell_size / 40);
	candyAmountDisplay.setPosition(candy.getPosition().x + candy.getGlobalBounds().width * 1.25, candy.getPosition().y);
}

void Shop::drawComponents()
{
	window->clear();
	window->draw(spikeController);
	window->draw(background);
	for (int i = 0; i < 20; i++)
		window->draw(*(tiles[i]));

	window->draw(upperHalf);
	window->draw(downHalf);
	window->draw(bottomRect);
	window->draw(spikeController);
	window->draw(candy);
	window->draw(candyAmountDisplay);
	window->draw(returnButton);
	window->display();
}

void Shop::open()
{
	bool selected = false;
	while (!selected)
	{
		sf::Event eventHandler;
		while (window->pollEvent(eventHandler))
		{
			if (eventHandler.type == sf::Event::MouseWheelScrolled)
			{
				offset += eventHandler.mouseWheelScroll.delta;
				moveTiles();
			}

			else if (eventHandler.type == sf::Event::MouseButtonReleased)
			{
				if (returnButton.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y))
				{
					selected = true;
				}
			}

			else if (eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Escape)
				selected = true;
		}

		drawComponents();
	}
}

Shop::~Shop()
{
	for (int i = 0; i < 20; i++)
		delete tiles[i];
}