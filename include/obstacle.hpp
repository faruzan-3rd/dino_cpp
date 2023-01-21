#ifndef __OBSTACLE_HPP
#define __OBSTACLE_HPP

#include <SFML/Graphics.hpp>
#include <random>


class Obstacle{
    public:
        static const int CACTUS = 0;
        static const int CROW = 1;

        Obstacle();
        Obstacle(int obstacle_type, std::vector<sf::Sprite> animation_frames, int y_offset, float anim_interval, int ground_height, int screen_width, int crow_height_limit);

        void update(int speed, float delta);

        void draw(sf::RenderWindow& window);

        sf::Vector2f get_position();

        sf::Vector2f get_dimension();

    private:
        int obstacle_type;
        std::vector<sf::Sprite> frames;
        sf::Vector2f position;
        int y_offset;
        float frame_interval;
        int cur_frame = 0;
        float anim_timer = 0;
};



class ObstacleGenerator{
    public:
        ObstacleGenerator(std::vector<sf::Sprite> cactuses, std::vector<std::vector<sf::Sprite>> crows, int y_offset, float anim_interval, int ground_height, int screen_width, int crow_height_limit, float generation_interval, float interval_modifier);
        
        bool update(const float& delta);

        void generate_obstacle(std::vector<Obstacle>& current_obstacles, int& objects_spd, int& spd_up_rate);

    private:
        float interval;
        const float interval_modifier;
        float timer{0};
        std::mt19937 engine;
        std::uniform_real_distribution<double> generator;
        std::vector<sf::Sprite> cactuses;
        std::vector<std::vector<sf::Sprite>> crows;
        int y_offset;
        int ground_height;
        int screen_width;
        int crow_height_limit;
        float anim_interval;
};


void update_obstacles(std::vector<Obstacle>& obstacles, const int& speed, const float& delta, sf::RenderWindow& window, bool physics_activated);

bool check_collision(const std::vector<Obstacle>& obstacles, const sf::Vector2f& dino_pos, const sf::Vector2f& dino_dim, bool& physics_enabled);


#endif