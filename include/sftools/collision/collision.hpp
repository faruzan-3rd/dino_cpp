#ifndef __COLLISION_HPP
#define __COLLISION_HPP

#include <SFML/Graphics.hpp>


bool is_colliding(const sf::Vector2f& box1_origin, const sf::Vector2f& box1_dimension, const sf::Vector2f& box2_origin, const sf::Vector2f& box2_dimension);



#endif