#pragma once
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>


class Bird : public sf::Sprite
{
private:
	enum direction {LEFT, RIGHT};

	direction direction;
	int verticalSpeed = 0;
	float horizontalSpeed;
	bool alive = true;
	sf::Texture texture1;
	sf::Texture texture2;

	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer deathSoundBuffer;
	sf::SoundBuffer pointSoundBuffer;
	sf::Sound jumpSound;
	sf::Sound deathSound;
	sf::Sound pointSound;

public:
	static sf::Image createBirdDown(std::string imgPath);
	static sf::Image createBirdUp(std::string imgPath);

	Bird();
	Bird(std::string texturePath);

	void move();
	void move(float,float);
	void bounce();
	void toss();
	void kill();
	void prepareSounds();
	void setVerticalSpeed(float);
	void setNewTextures(std::string imgPath);
	
	int getDirection();
	bool isAlive();
};

