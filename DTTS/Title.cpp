#include "Title.h"

Title::Title() :Title(40) {}

Title::Title(float characterSize)
{
	tekst = "Don't touch\n the spikes";
	font.loadFromFile("font/ariblk.ttf");
	setFont(font);
	setCharacterSize(characterSize);
	setFillColor(sf::Color(255, 255, 255));
	setString((tekst));
	disk.setFillColor(sf::Color::White);
}

sf::CircleShape Title::getDisk()
{
	return disk;
}


void Title::setDisk(float x, float y, float size) {
	disk.setRadius(size);

	disk.setPosition(x - disk.getRadius(), y - disk.getRadius());

}