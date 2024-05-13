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
#include "Player.h"
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
	sf::Music music;

	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
	sf::Texture texture5;
	sf::Texture texture6;
	sf::Texture worldBackgroundTex;
	Player* player;

	
	sf::Text pointText;

	sf::Text gameOverText;
	sf::RectangleShape playerHpBar;
	


	//game logic
	bool endGame;
	int points;
	int counter;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;


	//game objects
	std::vector<sf::Sprite> enemies_top;
	std::vector < sf::Sprite> enemies_bottom;
	std::vector < sf::Sprite> enemies_left;
	std::vector < sf::Sprite> enemies_right;
	sf::Sprite enemy_top;
	sf::Sprite enemy_bottom;
	sf::Sprite enemy_left;
	sf::Sprite enemy_right;

	sf::Sprite worldBackground;


	//private functions
	void initializeVariables();
	void initWindow();
	void initEnemies_top();
	void initEnemies_bottom();
	void initEnemies_left();
	void initEnemies_right();
	void initFonts();
	void initText();
	void initMusic();
	void initPlayer();
	void initWorld();
	void initHealthBar();
	void initScore();

	

public:
	//Constructors / Destructors
	Game();
	virtual ~Game();
	//accesors
	const bool running() const;
	const bool getEndGame() const;


	//Functions
	void spawnEnemy_top();
	void spawnEnemy_bottom();
	void spawnEnemy_left();
	void spawnEnemy_right();
	
	void pollEvents();
	
	void updateMousePositions();
	//void updateText();
	void updateEnemies_top();
	void updateEnemies_bottom();
	void updateEnemies_left();
	void updateEnemies_right();
	void updateHealthBar();
	void updateScore();

	void updateInput();
	void update();

	void renderEnemies(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);
	void renderWorld();
	void renderHealthBar(sf::RenderTarget& target);
	


	void render();


};

