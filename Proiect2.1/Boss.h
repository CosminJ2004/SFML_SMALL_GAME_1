#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
class Boss
{ private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::IntRect currentFrame;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private functions
	
	void initTexture();
	void initSprite();

public:
	Boss();
	virtual ~Boss();

	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;


	//Modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void render(sf::RenderTarget& target);
	//Functions
	
};

