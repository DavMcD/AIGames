// author Peter Lowe

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1200, 32 }, "SFML Game" },
	m_exitGame{ false }, //when true game will exit
	cat(),
	cow(),
	pig(),
	pig2(),
	sheep(),
	dog()
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	cow.setSeek(true);
	pig.setArrive(true);
	pig2.setArrive(true);
	sheep.setPursue(true);
}


Game::~Game()
{
}


void Game::run()
{
	sf::Clock clock;
	int timer = 0;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	sf::Vector2f dogPos = sf::Vector2f(0, 0);
	
	while (m_window.isOpen())
	{

		if (timer > 50)
		{
			cat.setPlayerPos(dog.getPos());
			cat.setRandAngle();
			timer = 0;
		}
		

		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
			timer++;
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{	
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;	
			}
			if (sf::Keyboard::Left == event.key.code)
			{
				dog.steer(true);
			}
			if (sf::Keyboard::Right == event.key.code)
			{
				dog.steer(false);
			}
		}
		if (sf::Event::KeyReleased == event.type)
		{
			if (sf::Keyboard::W == event.key.code)
			{
				cat.changeSpeed(true);
			}
			if (sf::Keyboard::S == event.key.code)
			{
				cat.changeSpeed(false);
			}
			if (sf::Keyboard::Up == event.key.code)
			{
				dog.changeSpeed(true);
			}
			if (sf::Keyboard::Down == event.key.code)
			{
				dog.changeSpeed(false);
			}
		}
		if (sf::Event::MouseButtonReleased == event.type)
		{
			cat.randSpeed();
			dog.randSpeed();
			cow.randSpeed();
			pig.randSpeed();
			pig2.randSpeed();
			sheep.randSpeed();
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	cat.wander();
	cow.setPlayerPos(dog.getPos());
	pig.setPlayerPos(dog.getPos());
	pig2.setPlayerPos(dog.getPos());
	sheep.setPlayerPos(dog.getPos());
	sheep.setPlayerVel(dog.getVel());
	cat.Update();
	cow.Update();
	pig.Update();
	pig2.Update();
	sheep.Update();
	dog.Update();


	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear();
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	cat.drawObject(m_window);
	dog.drawObject(m_window);
	cow.drawObject(m_window);
	pig.drawObject(m_window);
	pig2.drawObject(m_window);
	sheep.drawObject(m_window);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}


/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);


	catTex = sf::Texture();
	catTex.loadFromFile("ASSETS\\IMAGES\\cirCat.png");
	cat.loadSpr(sf::Sprite(catTex));

	cowTex = sf::Texture();
	cowTex.loadFromFile("ASSETS\\IMAGES\\cowFace.png");
	cow.loadSpr(sf::Sprite(cowTex));

	pigTex = sf::Texture();
	pigTex.loadFromFile("ASSETS\\IMAGES\\uggPig.png");
	pig.loadSpr(sf::Sprite(pigTex));

	pig2Tex = sf::Texture();
	pig2Tex.loadFromFile("ASSETS\\IMAGES\\cutepig.png");
	pig2.loadSpr(sf::Sprite(pig2Tex));

	sheepTex = sf::Texture();
	sheepTex.loadFromFile("ASSETS\\IMAGES\\sheep.png");
	sheep.loadSpr(sf::Sprite(sheepTex));

	dogTex = sf::Texture();
	dogTex.loadFromFile("ASSETS\\IMAGES\\sqDog.png");
	dog.loadSpr(sf::Sprite(dogTex));
}
