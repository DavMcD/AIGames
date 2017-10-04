#include "Object.h"



Object::Object() : spr()
{
	pos = sf::Vector2f(rand() % 1600, rand() % 1200);
	randSpeed();
	if (vel.x == 0 && vel.y == 0)
	{
		randSpeed();
	}
	speed = 2;
	arriveSpeed = 2;
	maxSpeed = 3;
	radAngle = 0;
}


Object::~Object()
{
}

sf::Vector2f Object::getPos()
{
	return pos;
}

void Object::drawObject(sf::RenderWindow &window)
{
	//Update();
	window.draw(spr);
}

void Object::Update()
{
	if (isSeeking)
	{
		seek();
	}
	else if (isFleeing)
	{
		flee();
	}
	else if (isArriving)
	{
		arrive();
	}
	else if (isPursuing)
	{
		pursue();
	}

	if (isArriving == false && isPursuing == false)
	{
		arriveSpeed = speed;
		pos += vel * speed;
	}
	spr.setPosition(pos);
	boundary();
	rotate();
}

void Object::rotate()
{
	float rotation = (atan2(vel.y, vel.x)) * 180 / 3.14159;
	rotation += 90;

	spr.setRotation(rotation);
	orientation = rotation;
}

void Object::loadSpr(sf::Sprite tempSpr)
{
	spr = tempSpr;
	spr.setScale(0.25, 0.25);

	spr.setOrigin(spr.getLocalBounds().width / 2, spr.getLocalBounds().width / 2);
	sf::Vector2f temp = pos;
	pos += spr.getOrigin();
	spr.setPosition(temp);
}

void Object::changeSpeed(bool speedUp)
{
	if (speedUp)
	{
		speed += 0.5;
	}
	else
	{
		speed -= 0.5;
	}
}

void Object::wander()
{
		/*if (!left)
		radAngle = -radAngle;*/

	float tempX = vel.x * cos(radAngle) - vel.y * sin(radAngle);
	vel.y = vel.x * sin(radAngle) + vel.y * cos(radAngle);
	vel.x = tempX;
}

void Object::seek()
{
	vel.x = playerPos.x - pos.x;
	vel.y = playerPos.y - pos.y;
	
	distFromPlayer = sqrt(vel.x * vel.x + vel.y * vel.y);
	vel.x = vel.x / distFromPlayer;
	vel.y = vel.y / distFromPlayer;
}

void Object::arrive()
{
	vel.x = playerPos.x - pos.x;
	vel.y = playerPos.y - pos.y;

	distFromPlayer = sqrt(vel.x * vel.x + vel.y * vel.y);

	vel.x = vel.x / distFromPlayer;
	vel.y = vel.y / distFromPlayer;

	if (distFromPlayer <= maxSpeed + distanceConst)
	{
		arriveSpeed = speed * ((distFromPlayer - (spr.getGlobalBounds().width / 1.2)) / (maxSpeed + distanceConst));

		if (arriveSpeed > 0.02)
			pos += vel * arriveSpeed;
	}
	else
	{
		arriveSpeed = speed;
		pos += vel * speed;
	}
}

void Object::pursue()
{
	sf::Vector2f seekToPoint = playerPos + (playerVel * 100.0f);
	vel.x = seekToPoint.x - pos.x;
	vel.y = seekToPoint.y - pos.y;

	distFromPlayer = sqrt(vel.x * vel.x + vel.y * vel.y);

	vel.x = vel.x / distFromPlayer;
	vel.y = vel.y / distFromPlayer;

	if (distFromPlayer <= maxSpeed + distanceConst)
	{
		arriveSpeed = speed * ((distFromPlayer - (spr.getGlobalBounds().width / 1.2)) / (maxSpeed + distanceConst));

		if (arriveSpeed > 0.02)
			pos += vel * arriveSpeed;
	}
	else
	{
		arriveSpeed = speed;
		pos += vel * speed;
	}
}

void Object::flee()
{
	vel.x = pos.x - playerPos.x;
	vel.y = pos.y - playerPos.y;

	float mag = sqrt(vel.x * vel.x + vel.y * vel.y);
	vel.x = vel.x / mag;
	vel.y = vel.y / mag;
}

void Object::setSeek(bool seekBool)
{
	isSeeking = seekBool;
}

void Object::setFlee(bool fleeBool)
{
	isFleeing = fleeBool;
}

void Object::setArrive(bool arriveBool)
{
	isArriving = arriveBool;
}

void Object::setPursue(bool pursueBool)
{
	isPursuing = pursueBool;
}

void Object::setRandAngle()
{
	radAngle = 1 * 3.14159265 / 180; //this is 10 degrees in radians : 10 * pi / 180
	randomNum = (rand() % 3);
	if (((playerPos.x - pos.x) * vel.y) - (playerPos.y - pos.y) * vel.x > 0)
	{
		radAngle = radAngle * randomNum;
		radAngle = -radAngle;
	}
	else if (((playerPos.x - pos.x) * vel.y) - (playerPos.y - pos.y) * vel.x < 0)
	{
		radAngle = radAngle * randomNum;
		//radAngle = radAngle;
	}
	else
	{
		randomNum--;
		radAngle = radAngle * randomNum;

	}
}

void Object::setPlayerPos(sf::Vector2f pPos)
{
	playerPos = pPos;
}

void Object::setPlayerVel(sf::Vector2f pVel)
{
	playerVel = pVel;
}

void Object::boundary()
{
	if (pos.x < -spr.getGlobalBounds().width)
	{
		pos.x = 1600;
	}
	else if (pos.x > 1600 + spr.getGlobalBounds().width)
	{
		pos.x = -spr.getGlobalBounds().width;
	}
	if (pos.y < -spr.getGlobalBounds().height)
	{
		pos.y = 1200;
	}
	else if (pos.y > 1200 + spr.getGlobalBounds().height)
	{
		pos.y = -spr.getGlobalBounds().height;
	}
}

void Object::randSpeed()
{
	vel = sf::Vector2f(rand() % 5, rand() % 5) - sf::Vector2f(3, 3);
}