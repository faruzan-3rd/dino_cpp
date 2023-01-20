#ifndef __OBSTACLE_HPP
#define __OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <random>


class ObstacleGenerator{
    public:
        ObstacleGenerator(const int obstacles_count, const float interval, const float interval_mod);
        
        int update(const float& delta);

    private:
        const int obs_count;
        float interval;
        const float interval_modifier;
        float timer{0};
        std::mt19937 engine;
        std::uniform_int_distribution<std::mt19937::result_type> generator;
};



#endif