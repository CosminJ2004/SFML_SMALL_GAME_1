#include "Bullet.h"
Bullet::Bullet(float x, float y) : x(x), y(y) {
    this->sprite.setPosition(x, y);
}


void Bullet::move( float x, float y, float target_x, float target_y)
{
    float direction_x = target_x - x;
    float direction_y = target_y - y;
    float length = std::sqrt(direction_x * direction_x + direction_y * direction_y);
    velocity_x = speed * direction_x / length;
    velocity_y = speed * direction_y / length;
    x += velocity_x;
    y += velocity_y;
        this->sprite.move(x, y);
       
    


}
 void Bullet:: update() {
        x += velocity_x;
        y += velocity_y;
    }
 void Bullet::initTexture()
 {
     bullet_texture.loadFromFile("Textures/bullet_texture.png");
     this->sprite.setTexture(this->bullet_texture);
 }
   

    bool Bullet::offScreen() {
        return x < 0 || x > 100 || y < 0 || y > 100;
    }


    void Bullet::calculateTrajectory(sf::Vector2f target) {
        float direction_x = target.x - x;
        float direction_y = target.y - y;
        float length = std::sqrt(direction_x * direction_x + direction_y * direction_y);
        velocity_x = speed * direction_x / length;
        velocity_y = speed * direction_y / length;
    }

   

