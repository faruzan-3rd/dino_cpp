#include "obstacle.hpp"
#include <iostream>


Obstacle::Obstacle(int obstacle_type, std::vector<sf::Sprite> animation_frames, int y_offset, float anim_interval, int ground_height, int screen_width, int crow_height_limit):
        obstacle_type(obstacle_type), frames(animation_frames), y_offset(y_offset), frame_interval(anim_interval)
{
    int crow_offset = 0;
    if(obstacle_type == Obstacle::CROW){
        std::mt19937 engine;
        std::uniform_real_distribution<double> generator;
        engine = std::mt19937((unsigned) time(NULL));
        generator = std::uniform_real_distribution<double>(0, 1);

        crow_offset -= generator(engine) * crow_height_limit;
    }

    position = sf::Vector2f(screen_width, ground_height + y_offset + crow_offset - animation_frames[0].getTextureRect().height);
}

Obstacle::Obstacle(){

}

void Obstacle::update(int speed, float delta){
    position.x -= speed * delta;
    anim_timer += delta;
    if(anim_timer >= frame_interval){
        anim_timer = 0;
        cur_frame = (cur_frame + 1) % frames.size();
    }
}

void Obstacle::draw(sf::RenderWindow& window){
    frames[cur_frame].setPosition(position);
    window.draw(frames[cur_frame]);
}


ObstacleGenerator::ObstacleGenerator(std::vector<sf::Sprite> cactuses, std::vector<std::vector<sf::Sprite>> crows, int y_offset, float anim_interval, int ground_height, int screen_width, int crow_height_limit, float generation_interval, float interval_modifier)
                                        :  cactuses(cactuses), crows(crows), y_offset(y_offset), anim_interval(anim_interval), ground_height(ground_height), screen_width(screen_width), crow_height_limit(crow_height_limit), interval(generation_interval), interval_modifier(interval_modifier)
{
    engine = std::mt19937((unsigned) time(NULL));
    generator = std::uniform_real_distribution<double>(0, 1);
} 


bool ObstacleGenerator::update(const float& delta){
    timer += delta;

    if(timer < interval) return 0;

    interval -= interval_modifier;
    timer = 0;

    return 1;
}


void ObstacleGenerator::generate_obstacle(std::vector<Obstacle>& current_obstacles, int& objects_spd, int& spd_up_rate){
    int obs_type = (int)(generator(engine) * 2);
    std::vector<sf::Sprite> frames;
    if(obs_type == Obstacle::CACTUS){
        frames = {cactuses[(int)(generator(engine) * cactuses.size())]};
    }else{
        frames = crows[(int)(generator(engine) * crows.size())];
    }

    Obstacle new_obstacle = Obstacle(obs_type, frames, y_offset, anim_interval, ground_height, screen_width, crow_height_limit);
    current_obstacles.push_back(new_obstacle);

    objects_spd += spd_up_rate;

}


void update_obstacles(std::vector<Obstacle>& obstacles, const int& speed, const float& delta, sf::RenderWindow& window){
    for(Obstacle& obs : obstacles){
        obs.update(speed, delta);
        obs.draw(window);
    }
}
