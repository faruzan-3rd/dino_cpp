#ifndef _DINO_BEHAV_HPP
#define _DINO_BEHAV_HPP

#include <SFML/Graphics.hpp>


namespace dino{

    void movement(float& dino_y_velocity, bool& is_grounded , bool& is_lying_down, const int& jump_power);

    void update_velocity(float& dino_y_velocity, const int& gravity, const float delta);

    void update_dino_pos(float& dino_y_velocity, sf::Vector2f& dino_pos, const float delta);

    void check_dino_status(float& dino_y_velocity, bool& is_grounded, sf::Vector2f& dino_pos, const int& dino_y_limit);

    void update_anim_sprite(sf::Sprite& dino_sprite, const std::vector<sf::Sprite>& frames, const sf::Sprite& static_dino, const sf::Sprite& lying_down_dino, int& frame_id, float& last_change, const float& interval, bool is_grounded, bool is_lying_down);
}



#endif