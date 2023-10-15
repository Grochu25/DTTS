#include "Menu.h"
#include "SkinTile.h"

void Menu::initialScale(float windowX)
{
    shopTexture = new sf::Texture();
    shopTexture->loadFromFile("img/shop.png");
    shopButton.setRadius(cell_size * 0.6);
    shopButton.setTexture(shopTexture);
    shopButton.setPosition(cell_size * 1, cell_size * 5);

    title = new Title(cell_size * 0.75);
    title->setDisk(windowX, cell_size * 7, cell_size * 2);
    title->setPosition(windowX - (title->getGlobalBounds().width / 2), cell_size * 2);

    GamePlay::initialScale();
    this->candy.setPosition(windowX - candy.getGlobalBounds().width, cell_size * 4.25);
}

void Menu::prepareSounds()
{
    buffer.loadFromFile("audio/button.wav");
    buttonSound.setBuffer(buffer);
}

Menu::Menu(sf::RenderWindow& window, float cell_size) {
    this->window = &window;
    this->cell_size = cell_size;
    readDataFile();
    initialScale(window.getSize().x / 2);
    prepareSounds();
    drawCounters();
}

Menu::~Menu()
{
    delete title;
}

void Menu::drawCounters()
{
    font.loadFromFile("font/ariblk.ttf"); 
    candyAmountDisplay.setFont(font);
    candyAmountDisplay.setFillColor(sf::Color(255,110,38));
    candyAmountDisplay.setString(std::to_string(candyAmount));
    candyAmountDisplay.setScale(cell_size/60, cell_size/60);
    candyAmountDisplay.setPosition(candy.getPosition().x + candy.getGlobalBounds().width*1.25, candy.getPosition().y);

    highScoreDisplay.setFont(font);
    highScoreDisplay.setFillColor(sf::Color(28, 188, 4));
    highScoreDisplay.setString("High Score: "+std::to_string(highScore));
    highScoreDisplay.setScale(cell_size / 50, cell_size / 50);
    highScoreDisplay.setPosition(window->getSize().x/2-highScoreDisplay.getGlobalBounds().width/2, cell_size*12);
}

void Menu::drawComponents()
{
    float x = window->getSize().x / 2;
    window->clear();
    window->draw(background);
    window->draw(title->getDisk());
    window->draw(*title);
    window->draw(bird);
    window->draw(spikeController);
    window->draw(candy);
    window->draw(candyAmountDisplay);
    window->draw(highScoreDisplay);
    window->draw(shopButton);
    window->display();
}


//opcje w menu
void Menu::start() {

    spikeController.setCellSize(cell_size);
    spikeController.placeSpikesLR(0);
    bool start = false;

    while (!start && window->isOpen())
    {
        sf::Event eventHandler;
        while (window->pollEvent(eventHandler))
        {
            if (eventHandler.type == sf::Event::MouseButtonReleased && shopButton.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))
            {
                buttonSound.play();
                shop = new Shop(window, cell_size);
                shop->open();
                bird.setNewTextures(shop->getSkinPath());
                delete shop;
            }

            else if ((eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Space) ||
                eventHandler.type == sf::Event::MouseButtonReleased)
                start = true;

            else if ((eventHandler.type == sf::Event::KeyPressed && eventHandler.key.code == sf::Keyboard::Escape) ||
                eventHandler.type == sf::Event::Closed)
                window->close();
        }

        drawComponents();
    }
}