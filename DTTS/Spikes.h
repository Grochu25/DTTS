#pragma once
#include <sfml/Graphics.hpp>
#include <random>
#include <ctime>

class Spikes : public sf::Drawable
{
private:
    int counter = 1;
    float cell_size;
    bool spikesLR[12];
    sf::ConvexShape spikes[16];
    sf::Color actualColor;

    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    int random(int max);
    void placeSpikesTB();   //generowanie kolcow na gorze i na dole
    void placeSpikesLR(int counter);  //generowanie kolcow prawo lewo 
    bool collisionSpikes(float coordinateY);
    void setCellSize(float cell_size);
    void setColor(sf::Color);
};
