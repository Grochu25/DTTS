#include "GamePlay.h"


void writeDataFile(GamePlay* gp)
{
    try
    {
        std::ofstream dataFile("data", std::ios::binary|std::ios::out);
        int hisc = gp->highScore;
        if (gp->counter.getScore() > gp->highScore)
            hisc = gp->counter.getScore();

        dataFile.write(reinterpret_cast<char*>(&hisc), sizeof(int));
        dataFile.write(reinterpret_cast<char*>(&gp->candyAmount), sizeof(int));

        for (int i = 0; i < 20; i++)
            dataFile.write(reinterpret_cast<char*>(&gp->boughtSkins[i]), sizeof(bool));
        dataFile.close();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
}

GamePlay::GamePlay(sf::RenderWindow &window, float cell_size)
{
    this->window = &window;
    this->cell_size = cell_size;
    initialScale();
    readDataFile();
}

void GamePlay::readDataFile()
{

    try
    {
        boughtSkins = new bool[20];

        std::ifstream dataFile("data", std::ios::binary);
        dataFile.read(reinterpret_cast<char*>(&highScore), sizeof(int));
        dataFile.read(reinterpret_cast<char*>(&candyAmount), sizeof(int));
        for (int i = 0; i < 20; i++)
            dataFile.read(reinterpret_cast<char*>(&boughtSkins[i]), sizeof(bool));

        dataFile.close();
    }
    catch (std::exception e)
    {
        std::cout << e.what() << std::endl;
    }
}

void GamePlay::initialScale()
{
    bird.scale(cell_size*1.25 / 290,  cell_size * 1.25 / 290);
    bird.setPosition(this->window->getSize().x / 2 - bird.getGlobalBounds().width/2, cell_size * 6.5);

    background.setPosition(cell_size / 2, cell_size / 2);
    background.setSize(sf::Vector2f(cell_size * 8, cell_size * 13));
    background.setOutlineThickness(cell_size / 2);
    background.setOutlineColor(sf::Color(166, 166, 166));
    background.setFillColor(sf::Color(120,120,120));

    counter.setCharacterSize(cell_size * 2);
    counter.setOrigin(cell_size, cell_size);
    counter.setPosition(this->window->getSize().x / 2, cell_size * 7);
    counter.setFillColor(sf::Color(120,120,120));

    spikeController.setColor(sf::Color(166, 166, 166));

    candy.scale(cell_size / 340, cell_size / 340);
}

void GamePlay::drawComponents()
{
    window->clear();
    window->draw(background);
    if (counter.getScore() >= 10) counter.setPosition(this->window->getSize().x / 2, cell_size * 7);
    window->draw(counter.getDisk());
    window->draw(counter);
    window->draw(bird);
    window->draw(spikeController);
    if(candy.isVisible()) window->draw(candy);
    window->display();
}

void GamePlay::changeColor()
{
    int r = ((static_cast<int>(background.getFillColor().r)) + 41) %256;
    int g = ((static_cast<int>(background.getFillColor().g)) + 87) %256;
    int b = ((static_cast<int>(background.getFillColor().b)) + 163) %256;

    background.setFillColor(sf::Color(r, g, b));
    counter.setFillColor(sf::Color(r, g, b));
}

void GamePlay::placeCandy()
{
    if(candy.getPosition().x != cell_size*1 && !candy.isVisible())
        candy.setPosition(cell_size*1, cell_size * spikeController.random(9) + (cell_size*2));

    else if(candy.getPosition().x != cell_size * 7 && !candy.isVisible())
        candy.setPosition(cell_size * 7, cell_size * spikeController.random(9) + (cell_size*2));

    candy.setVisible(true);
}

void GamePlay::moveBird()
{
    sf::Clock birdTiming;
    sf::Clock deathCounter;
    
    while (!gameOver)
    {
        if (birdTiming.getElapsedTime().asMilliseconds() >= 30)
        {
            //if bird is close enough to borders, he can touch spikes
            if ((bird.getPosition().x > cell_size * 6.5 && bird.getDirection()==1) 
                || (bird.getPosition().x <= cell_size && bird.getDirection() == 0))
            {
                //if bird touch spikes
                coordinateY = bird.getPosition().y;
                if (spikeController.collisionSpikes(coordinateY) == 1)
                {
                    if (bird.isAlive())deathCounter.restart();
                    bird.kill();
                    writeDataFile(this);
                }

                //if bird is close enough to borders and bounce
                if ((bird.getPosition().x > cell_size * 7 && bird.getDirection() == 1)
                    || (bird.getPosition().x <= cell_size && bird.getDirection() == 0))
                {
                    bird.bounce();
                    if (bird.isAlive()) counter.addPoint();
                    if (counter.getScore() % 5 == 0) changeColor();
                    spikeController.placeSpikesLR(counter.getScore());
                    placeCandy();
                }
            }
            //if bird is touching top or bottom spikes
            if (bird.getPosition().y >= cell_size * 12 || bird.getPosition().y <= cell_size)
            {
                bird.setVerticalSpeed((bird.getPosition().y>cell_size)?-15:15);
                if (bird.isAlive())deathCounter.restart();
                bird.kill();
                writeDataFile(this);
            }

            bird.move();
            if (candy.isColiding(bird.getGlobalBounds()))
                candyAmount++;

            birdTiming.restart();
        }

        if (!bird.isAlive() && deathCounter.getElapsedTime().asSeconds() >= 1.5)
            gameOver = true;
    }
}

void GamePlay::start()
{
    sf::Thread birdMoveThread(&GamePlay::moveBird, this);
    birdMoveThread.launch();
    bird.toss();

    spikeController.setCellSize(cell_size);
    spikeController.placeSpikesTB();

    while (!gameOver && window->isOpen())
    {
        sf::Event eventHandler;
        while (window->pollEvent(eventHandler))
        {
            if (eventHandler.type == sf::Event::Closed)
            {
                birdMoveThread.terminate();
                gameOver = true;
                window->close();
            }
            else if ((eventHandler.type == sf::Event::MouseButtonReleased 
                    || eventHandler.type == sf::Event::KeyPressed&& eventHandler.key.code == sf::Keyboard::Space)  && bird.isAlive())
            {
                bird.toss();
            }
        }
        drawComponents();
    }
}