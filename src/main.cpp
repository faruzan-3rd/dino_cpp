#include <SFML/Graphics.hpp>
#include <iostream>
#include "sftools/assets/load.hpp"
#include "dino_behaviour.hpp"
#include "ground_animation.hpp"
#include "obstacle.hpp"


void reinitialize_game(std::map<std::string, std::string>& cfg, int& objects_spd, ObstacleGenerator& generator, sf::Vector2f& dino_pos, int& dino_y_lim,
                       float& jump_velo, bool& is_grounded, bool& is_lying_down, float& delta, float& last_update, int& dino_anim_frame, float& dino_anim_upd_timer,
                       bool& physics_activated, std::vector<Obstacle>& current_obstacles, sf::Vector2f& ground1_pos, sf::Vector2f ground2_pos, int& ground_height);


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
    int obstacles_y_offset{std::stoi(cfg["obstacles_y_offset"])};
    int crow_height_limit{std::stoi(cfg["crow_height_limit"])};
    float init_obj_interval{std::stof(cfg["init_obj_interval"])};
    float interval_decay{std::stof(cfg["interval_decay"])};

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
    std::vector<sf::Sprite> cactuses{sprites["cactus1"], sprites["cactus2"], sprites["cactus3"]};
    std::vector<std::vector<sf::Sprite>> crows{ {sprites["crow1"], sprites["crow2"]} };
    ObstacleGenerator generator(cactuses, crows, obstacles_y_offset, anim_upd_interval, ground_height, width, crow_height_limit, init_obj_interval, interval_decay);
    std::vector<Obstacle> current_obstacles(0);

    // Other
    sf::Clock clock;
    int dino_anim_frame{0};
    float dino_anim_upd_timer{0};
    bool physics_activated = true;
    sprites["game_over"].setPosition(sf::Vector2f(width * 0.5 - 96, 100));
    sprites["again"].setPosition(sf::Vector2f(width * 0.5 - 15, 150));

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
        if(generator.update(delta)){
            generator.generate_obstacle(current_obstacles, objects_spd, speed_up_rate);
        }
        update_obstacles(current_obstacles, objects_spd, delta, window, physics_activated);

        sf::Vector2f dino_dim;
        if(is_lying_down) dino_dim = sf::Vector2f(sprites["dino_lie"].getTextureRect().width, sprites["dino_lie"].getTextureRect().height);
        else dino_dim = sf::Vector2f(sprites["dino_static"].getTextureRect().width, sprites["dino_static"].getTextureRect().height);

        if(physics_activated){
            check_collision(current_obstacles, dino_pos + sf::Vector2f(0, is_lying_down * lie_down_offset), dino_dim, physics_activated);
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
        }
        else{
            window.draw(sprites["game_over"]);
            window.draw(sprites["again"]);

            reinitialize_game(cfg, objects_spd, generator, dino_pos, dino_y_lim, jump_velo, is_grounded, is_lying_down, delta, last_update,
                                dino_anim_frame, dino_anim_upd_timer, physics_activated, current_obstacles, ground1_pos, ground2_pos, ground_height);
        }

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


void reinitialize_game(std::map<std::string, std::string>& cfg, int& objects_spd, ObstacleGenerator& generator, sf::Vector2f& dino_pos, int& dino_y_lim,
                       float& jump_velo, bool& is_grounded, bool& is_lying_down, float& delta, float& last_update, int& dino_anim_frame, float& dino_anim_upd_timer,
                       bool& physics_activated, std::vector<Obstacle>& current_obstacles, sf::Vector2f& ground1_pos, sf::Vector2f ground2_pos, int& ground_height){
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) return;

    objects_spd = std::stoi(cfg["ground_default_spd"]);
    generator.reset();
    dino_pos = sf::Vector2f(50, dino_y_lim);
    jump_velo = 0;
    is_grounded = true, is_lying_down = false;
    delta = 0;
    last_update = 0;
    dino_anim_frame = 0;
    dino_anim_upd_timer = 0;
    physics_activated = true;
    current_obstacles.clear();
    ground1_pos = sf::Vector2f(0, ground_height);
    ground2_pos = sf::Vector2f(0, ground_height);

}