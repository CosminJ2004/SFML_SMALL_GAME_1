#pragma once
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include <vector>
#include <ctime>
#include <sstream>

/*
Class that acts like the game engine
Wrapper class
*/
class Game
{
private:
	//variables
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//mouse pso
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//resources
	sf::Font font;

	//text
	sf::Text uiText;



	//game logic
	bool endGame;
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	//game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;



	//private functions
	void initializeVariables();
	void initWindow();
	void initEnemies();
	void initFonts();
	void initText();

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//accesors
	const bool running() const;
	const bool getEndGame() const;


	//Functions
	void spawnEnemy();
	
	void pollEvents();
	
	void updateMousePositions();
	void updateText();
	void updateEnemies();

	void update();

	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);

	
	void render();


};

