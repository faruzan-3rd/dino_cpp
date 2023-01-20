#ifndef _GROUND_ANIM_HPP
#define _GROUND_ANIM_HPP


#include <SFML/Graphics.hpp>


namespace ground{

    void set_initial_pos(const sf::Sprite& ground_sprite, sf::Vector2f& ground1_pos, sf::Vector2f& ground2_pos);

    void move_and_check(sf::Sprite& ground1_sprite, sf::Sprite& ground2_sprite,
             sf::Vector2f& ground1_pos, sf::Vector2f& ground2_pos, const int& speed, const float delta);
}



#endif