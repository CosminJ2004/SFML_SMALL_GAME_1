#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include "Bullet.h"
enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, MOVING_UP};
class Player
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;
	float velocityMax;
	float velocityMin;
	float attackCooldown;
	float attackCooldownMax;
	float x, y;
	float target_x, target_y;

	//Animation
	sf::Vector2f velocity;
	sf::Clock animationTimer;
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	

	std::vector<Bullet> bullets;
	Bullet bullet;


public:
	Player();
	virtual ~Player();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;
	const bool& getAnimSwitch();

	void shoot(float x, float y,sf::Vector2f target);
	void draw();

	void updateMovement();
	void updateAnimations();
	
	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void resetAnimationTimer();

	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};
