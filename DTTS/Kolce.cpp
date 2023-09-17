#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include "Bird.h"
#include "Menu.h"

float cell = 72;

//int WinMain()
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 2000;   //wygladzenie krawedzi 
    cell = sf::VideoMode::getDesktopMode().height / 19;
    sf::RenderWindow window(sf::VideoMode(cell * 9, cell * 14), "Kolce", sf::Style::Default, settings);
    

    while (window.isOpen())
    {
        
        Menu* y = new Menu(window, cell);
        y->start();
        delete y;

        GamePlay* x = new GamePlay(window, cell);
        x->start();
        delete x;
        
    }

    return 0;
}