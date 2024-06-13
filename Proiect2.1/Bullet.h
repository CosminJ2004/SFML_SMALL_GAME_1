#pragma once
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
class Bullet
{
private:

	
	float x, y;
	
	

public:

	float speed;
	float velocity_x, velocity_y;
	sf::Sprite sprite;
	sf::Texture bullet_texture;
	Bullet(float x, float y);
	virtual ~Bullet();
	void update();
	void draw();
	void initTexture();
	bool offScreen();
	void move(float x, float y, float target_x, float target_y);
	void calculateTrajectory(sf::Vector2f target);

};

