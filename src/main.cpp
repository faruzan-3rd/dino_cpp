#include <SFML/Graphics.hpp>
#include <iostream>
#include "sftools/assets/load.hpp"
#include "dino_behaviour.hpp"
#include "ground_animation.hpp"
#include "obstacle.hpp"


int main(){
    // Basic configs
    std::map<std::string, std::string> cfg = load_config("assets/config.txt");
    int width{std::stoi(cfg["width"])};
    int height{std::stoi(cfg["height"])};
    sf::RenderWindow window(sf::VideoMode(width, height), "Dino game");
    window.setFramerateLimit(std::stoi(cfg["frame_rate_limit"]));

    // Load sprites
    sf::Texture texture;
    texture.loadFromFile("assets/sprites.png");
    std::map<std::string, sf::Sprite> sprites = load_from_spritesheet("assets/sprites_load.txt", texture);

    // Assign sprites to variables
    sf::Sprite dino_sp = sprites["dino_static"];
    sf::Sprite ground1 = sprites["ground"], ground2 = sprites["ground"];
    std::vector<sf::Sprite> run_anim_frames{sprites["dino_run_1"], sprites["dino_run_2"]};

    // Params
    int jump_pow{std::stoi(cfg["jump_pow"])};
    int gravity{std::stoi(cfg["gravity"])};
    int dino_y_lim{std::stoi(cfg["dino_max_y"])};
    int objects_spd{std::stoi(cfg["ground_default_spd"])};
    float anim_upd_interval{std::stof(cfg["dino_anim_interval"])};
    int lie_down_offset{std::stoi(cfg["lie_down_offset"])};
    int speed_up_rate{std::stoi(cfg["dino_speed_up"])};
    int ground_height{std::stoi(cfg["ground_height"])};

    // Physics
    sf::Vector2f dino_pos(50, dino_y_lim);
    sf::Vector2f ground1_pos(0, ground_height), ground2_pos(0, ground_height);
    float jump_velo{};
    bool is_grounded{true}, is_lying_down{false};
    float delta{}, last_update{};

    // Set initial position
    dino_sp.setPosition(dino_pos);
    ground::set_initial_pos(ground1, ground1_pos, ground2_pos);

    // Obstacles
    std::vector<sf::Sprite> obstacles{sprites["cactus1"], sprites["crow1"]};
    ObstacleGenerator generator(obstacles.size(), std::stof(cfg["init_obj_interval"]), std::stof(cfg["interval_decay"]));
    std::vector<sf::Sprite> current_obstacles(0);
    int obstacles_y_offset{10};

    // Other
    sf::Clock clock;
    int dino_anim_frame{0};
    float dino_anim_upd_timer{0};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
                return 0;
            }
        }
        window.clear(sf::Color::White);

        // OBSTACLES
        int generator_ret = generator.update(delta);
        if(generator_ret != -1){
            // copied
            sf::Sprite new_obstacle = obstacles[generator_ret];

            new_obstacle.setPosition(sf::Vector2f(width, ground_height - new_obstacle.getTextureRect().height + obstacles_y_offset));
            current_obstacles.push_back(new_obstacle);

            objects_spd += speed_up_rate;
        }

        std::vector<sf::Sprite> new_obs;
        for(sf::Sprite obstacle : current_obstacles){
            obstacle.setPosition(obstacle.getPosition().x - delta * objects_spd, obstacle.getPosition().y);

            if(obstacle.getPosition().x > -150){
                window.draw(obstacle);
                new_obs.push_back(obstacle);
            }
        }

        current_obstacles = new_obs;


        // DINO STUFF
        dino_anim_upd_timer += delta;
        dino::movement(jump_velo, is_grounded, is_lying_down, jump_pow);
        dino::update_dino_pos(jump_velo, dino_pos, delta);
        dino::update_anim_sprite(dino_sp, run_anim_frames, sprites["dino_static"], sprites["dino_lie"], dino_anim_frame, dino_anim_upd_timer, anim_upd_interval, is_grounded, is_lying_down);
        dino::update_velocity(jump_velo, gravity, delta);
        dino::check_dino_status(jump_velo, is_grounded, dino_pos, dino_y_lim);
        sf::Vector2f final_pos = dino_pos;
        final_pos.y += is_lying_down * lie_down_offset;
        dino_sp.setPosition(final_pos);

        // GROUND STUFF
        ground::move_and_check(ground1, ground2, ground1_pos, ground2_pos, objects_spd, delta);

        // DRAW
        window.draw(dino_sp);
        window.draw(ground1);
        window.draw(ground2);
        window.display();
        delta = (clock.getElapsedTime().asMilliseconds() - last_update) / 1000.0f;
        last_update = clock.getElapsedTime().asMilliseconds();
    }

    return 0;
}