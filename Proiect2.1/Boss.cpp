#include "Boss.h"
void Boss::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/boss.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Boss::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//this->currentFrame = sf::IntRect(0, 0, 64, 64);
//	this->sprite.setTextureRect(this->currentFrame);
	//Resize the sprite
	this->sprite.scale(0.5f, 0.5f);
}

Boss::Boss()
{
	
	this->initTexture();
	this->initSprite();
}

Boss::~Boss()
{

}

const sf::Vector2f& Boss::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Boss::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Boss::getHp() const
{
	return this->hp;
}

const int& Boss::getHpMax() const
{
	return this->hpMax;
}

void Boss::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Boss::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);

}

void Boss::setHp(const int hp)
{
	this->hp = hp;
}

void Boss::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Boss::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}