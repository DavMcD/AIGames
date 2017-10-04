// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Player.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	sf::Texture catTex;
	sf::Texture cowTex;
	sf::Texture pigTex;
	sf::Texture pig2Tex;
	sf::Texture sheepTex;
	sf::Texture dogTex;

	Object cow;
	Object pig;
	Object pig2;
	Object cat;
	Object sheep;
	Player dog;

};

#endif // !GAME

