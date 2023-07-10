#include "Spikes.h"

std::mt19937 generator(time(nullptr));

int Spikes::random(int max)
{
    std::uniform_int_distribution<int>distribution(0, max);
    int s = distribution(generator);
    return s;
}

void Spikes::placeSpikesTB()
{
    for (int i = 0; i < 8; i++)
    {
        spikes[i].setPointCount(3);
        spikes[i].setFillColor(actualColor);
        spikes[i].setPoint(0, sf::Vector2f(cell_size / 2 + cell_size * i, cell_size * 13.75));
        spikes[i].setPoint(1, sf::Vector2f(cell_size / 2 + cell_size * (i + 0.5), cell_size * 13));
        spikes[i].setPoint(2, sf::Vector2f(cell_size / 2 + cell_size * (i + 1), cell_size * 13.75));
    }

    for (int i = 0; i < 8; i++)
    {
        spikes[i + 8].setPointCount(3);
        spikes[i + 8].setFillColor(sf::Color(actualColor));
        spikes[i + 8].setPoint(0, sf::Vector2f(cell_size / 2 + cell_size * i, cell_size * 0.25));
        spikes[i + 8].setPoint(1, sf::Vector2f(cell_size / 2 + cell_size * (i + 0.5), cell_size));
        spikes[i + 8].setPoint(2, sf::Vector2f(cell_size / 2 + cell_size * (i + 1), cell_size * 0.25));
    }
}

void Spikes::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setFillColor(sf::Color(actualColor));
    for (int i = 0; i < 12; i++)
    {
        if (spikesLR[i] == true && counter % 2 == 1)
        {
            triangle.setPoint(0, sf::Vector2f(cell_size * 0.4, i * cell_size + cell_size));
            triangle.setPoint(1, sf::Vector2f(cell_size, (i + 0.5) * cell_size + cell_size));
            triangle.setPoint(2, sf::Vector2f(cell_size * 0.4, (i + 1) * cell_size + cell_size));
            target.draw(triangle, states);
        }
        else if (spikesLR[i] == true && counter % 2 == 0)
        {
            triangle.setPoint(0, sf::Vector2f(cell_size * 8.6, i * cell_size + cell_size));
            triangle.setPoint(1, sf::Vector2f(cell_size * 8, (i + 0.5) * cell_size + cell_size));
            triangle.setPoint(2, sf::Vector2f(cell_size * 8.6, (i + 1) * cell_size + cell_size));
            target.draw(triangle, states);
        }
    }

    for (int i = 0; i < 16; i++) target.draw(spikes[i]);
}

void Spikes::placeSpikesLR(int counter)
{
    this->counter = counter;
    for (int i = 0; i < 12; i++)   //clearing array
    {
        spikesLR[i] = false;
    }

    int number_of_spikes = counter / 5;
    if (number_of_spikes >= 12)
    {
        number_of_spikes = 11;
    }
    else if (number_of_spikes == 0 && counter != 0)
    {
        number_of_spikes = 1;   
    }

    for (int i = 0; i < number_of_spikes; i++)
    {
        int index;
        do
        {
            index = random(11);
        } while (spikesLR[index] == true);
        spikesLR[index] = true;
    }
    placeSpikesTB();
}

bool Spikes::collisionSpikes(float coordinateY)
{
  
    for (int i = 0; i < 12; i++)
    {
        if (spikesLR[i] == true)
        {
            if ((coordinateY+0.5*cell_size > (i * cell_size + cell_size-0.25*cell_size)) && 
                (coordinateY+ 0.5 * cell_size < ((i + 1) * cell_size + cell_size+ 0.25 * cell_size)))
            {
                return 1;
            }
        }
    }
    return 0;

}

void Spikes::setCellSize(float cell_size)
{
    this->cell_size = cell_size;
}

void Spikes::setColor(sf::Color color)
{
    actualColor = color;
}