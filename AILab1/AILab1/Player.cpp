#include "Player.h"


Player::Player() : spr()
{
	pos = sf::Vector2f(rand() % 1600, rand() % 1200);
	randSpeed();
	if (vel.x == 0 && vel.y == 0)
	{
		randSpeed();
	}
	speed = 2.5;
}


Player::~Player()
{
}

sf::Vector2f Player::getPos()
{
	return pos;
}

sf::Vector2f Player::getVel()
{
	return vel;
}

void Player::drawObject(sf::RenderWindow &window)
{
	//Update();
	window.draw(spr);
}

void Player::Update()
{
	pos += vel * speed;
	spr.setPosition(pos);
	boundary();
	rotate();
}

void Player::rotate()
{
	float rotation = (atan2(vel.y, vel.x)) * 180 / 3.14159;
	rotation += 90;

	spr.setRotation(rotation);
	orientation = rotation;

}

void Player::loadSpr(sf::Sprite tempSpr)
{
	spr = tempSpr;
	spr.setScale(0.25, 0.25);

	spr.setOrigin(spr.getLocalBounds().width / 2, spr.getLocalBounds().width / 2);
	sf::Vector2f temp = pos;
	pos += spr.getOrigin();
	spr.setPosition(temp);
}

void Player::changeSpeed(bool speedUp)
{
	if (speedUp)
	{
		speed += 0.5;
	}
	else
	{
		speed -= 0.5;
	}

	if (speed > maxSpeed)
	{
		speed = maxSpeed;
	}
	else if (speed < -maxSpeed)
	{
		speed = -maxSpeed;
	}
}

void Player::steer(bool left)
{
	float radAngle = 10 * 3.14159265 / 180; //this is 10 degrees in radians : 10 * pi / 180

	if (!left)
		radAngle = -radAngle;

	float tempX = vel.x * cos(radAngle) - vel.y * sin(radAngle);
	vel.y = vel.x * sin(radAngle) + vel.y * cos(radAngle);
	vel.x = tempX;

}

void Player::boundary()
{
	if (pos.x < -spr.getGlobalBounds().width)
	{
		pos.x = 1600;
	}
	else if (pos.x > 1600 + spr.getGlobalBounds().width)
	{
		pos.x = -spr.getGlobalBounds().width/2;
	}
	if (pos.y < -spr.getGlobalBounds().height)
	{
		pos.y = 1200;
	}
	else if (pos.y > 1200 + spr.getGlobalBounds().height)
	{
		pos.y = -spr.getGlobalBounds().height/2;
	}
}

void Player::randSpeed()
{
	vel = sf::Vector2f(rand() % 5, rand() % 5) - sf::Vector2f(3, 3);
}
