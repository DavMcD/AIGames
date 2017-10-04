
#pragma once
#include <SFML/Graphics.hpp>
class Player
{
public:
	Player();
	~Player();
	sf::Vector2f getPos();
	sf::Vector2f getVel();
	void drawObject(sf::RenderWindow & window);
	void Update();
	void rotate();
	void loadSpr(sf::Sprite tempSpr);

	void changeSpeed(bool speedUp);

	void steer(bool left);

	void boundary();

	void randSpeed();

private:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Sprite spr;
	float speed;
	const float maxSpeed = 3.0f;
	float orientation = 0;
};

