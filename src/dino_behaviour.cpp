#include "dino_behaviour.hpp"


void dino::movement(float& dino_y_velocity, bool& is_grounded, bool& is_lying_down, const int& jump_power){
    if(!is_grounded) return;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        is_lying_down = true;
        return;
    }else{
        is_lying_down = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        is_grounded = false;
        dino_y_velocity = -(float)jump_power;
    }
}


void dino::update_velocity(float& dino_y_velocity, const int& gravity, const float delta){
    dino_y_velocity += delta * abs(gravity);
}


void dino::update_dino_pos(float& dino_y_velocity, sf::Vector2f& dino_pos, const float delta){
    dino_pos.y += delta * dino_y_velocity;
}


void dino::check_dino_status(float& dino_y_velocity, bool& is_grounded, sf::Vector2f& dino_pos, const int& dino_y_limit){
    if(dino_pos.y < dino_y_limit) return;

    is_grounded = true;
    dino_pos.y = dino_y_limit;
    dino_y_velocity = 0;
}


void dino::update_anim_sprite(sf::Sprite& dino_sprite, const std::vector<sf::Sprite>& frames, const sf::Sprite& static_dino, const sf::Sprite& lying_down_dino, int& frame_id, float& last_change, const float& interval, bool is_grounded, bool is_lying_down){
    if(!is_grounded){
        dino_sprite.setTextureRect(static_dino.getTextureRect());
        last_change = 0;
        return;
    }

    if(is_lying_down){
        dino_sprite.setTextureRect(lying_down_dino.getTextureRect());
        return;
    }

    if(last_change < interval) return;


    frame_id = (frame_id + 1) % frames.size();
    dino_sprite.setTextureRect(frames[frame_id].getTextureRect());
    last_change = 0;
}

