#include "ground_animation.hpp"


void ground::set_initial_pos(const sf::Sprite& ground_sprite, sf::Vector2f& ground1_pos, sf::Vector2f& ground2_pos){

    ground1_pos.x = 0;
    ground2_pos.x = ground1_pos.x + ground_sprite.getGlobalBounds().width;
}


void ground::move_and_check(sf::Sprite& ground1_sprite, sf::Sprite& ground2_sprite, sf::Vector2f& ground1_pos, sf::Vector2f& ground2_pos, const int& speed, const float delta){
    ground1_pos.x -= speed * delta;
    ground2_pos.x -= speed * delta;

    if(ground1_pos.x < -ground1_sprite.getGlobalBounds().width) ground1_pos.x = ground2_pos.x + ground2_sprite.getGlobalBounds().width;
    if(ground2_pos.x < -ground2_sprite.getGlobalBounds().width) ground2_pos.x = ground1_pos.x + ground1_sprite.getGlobalBounds().width;

    ground1_sprite.setPosition(ground1_pos);
    ground2_sprite.setPosition(ground2_pos);
}