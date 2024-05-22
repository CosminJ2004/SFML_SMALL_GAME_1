#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 5.f;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
	this->animState = PLAYER_ANIMATION_STATES::IDLE;

}
void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->currentFrame.left = 0.f;
}
void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(this->currentFrame);
	//Resize the sprite
	this->sprite.scale(2.5f,2.5f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Player::~Player()
{

}

const bool& Player::getAnimSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}
const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
	
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}
/*
void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}*/
void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}
void Player::updateMovement()
{
	
		//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->sprite.move((-1)*this->movementSpeed, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->sprite.move(this->movementSpeed, 0.f);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->sprite.move(0.f, (- 1)* this->movementSpeed);
		this->animState = PLAYER_ANIMATION_STATES::MOVING_UP;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->sprite.move(0.f, this->movementSpeed);
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::S)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

void Player::updateAnimations()
{
	
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 200.f||this->getAnimSwitch( ))
		{
			this->currentFrame.top =128.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left > 512.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 40.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 192.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left > 512.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 40.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 64.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left > 512.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_UP)
	{
		if (this->animationTimer.getElapsedTime().asMilliseconds() >= 40.f || this->getAnimSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left > 512.f)
				this->currentFrame.left = 0;

			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}

		this->sprite.setScale(3.f, 3.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else
		this->animationTimer.restart();
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;
}

//Functions
void Player::update()
{
	this->updateAttack();
	this->updateMovement();
	this->updateAnimations();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}