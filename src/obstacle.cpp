#include "obstacle.hpp"


ObstacleGenerator::ObstacleGenerator(const int obstacles_count, const float interval, const float interval_mod)
                                        : obs_count(obstacles_count), interval(interval), interval_modifier(interval_mod)
    {
        engine = std::mt19937((unsigned) time(NULL));
        generator = std::uniform_int_distribution<std::mt19937::result_type>(0, obs_count - 1);
    } 


int ObstacleGenerator::update(const float& delta){
    timer += delta;

    if(timer < interval) return -1;

    interval -= interval_modifier;
    timer = 0;

    return (int)generator(engine);
}
