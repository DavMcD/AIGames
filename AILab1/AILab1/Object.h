#pragma once
#include <SFML/Graphics.hpp>
class Object
{
public:
	Object();
	~Object();
	sf::Vector2f getPos();
	void drawObject(sf::RenderWindow & window);
	void Update();
	void rotate();
	void loadSpr(sf::Sprite tempSpr);

	void changeSpeed(bool speedUp);

	void boundary();

	void randSpeed();
	void wander();

	void seek();

	void arrive();

	void pursue();

	void flee();

	void setSeek(bool seekBool);

	void setFlee(bool fleeBool);

	void setArrive(bool arriveBool);

	void setPursue(bool pursueBool);

	void setRandAngle();

	void setPlayerPos(sf::Vector2f pPos);

	void setPlayerVel(sf::Vector2f pVel);

private:
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Sprite spr;
	sf::Vector2f playerPos;
	sf::Vector2f playerVel;
	float radAngle;
	int randomNum;
	float speed;
	float arriveSpeed;
	float distFromPlayer;
	float maxSpeed;
	const float distanceConst = 150;
	float orientation = 0;
	bool isSeeking = false;
	bool isFleeing = false;
	bool isArriving = false;
	bool isPursuing = false;
};

