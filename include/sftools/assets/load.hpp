#ifndef _SFT_ASSETS_LOAD_HPP
#define _SFT_ASSETS_LOAD_HPP


#include <map>
#include <SFML/Graphics.hpp>


std::map<std::string, sf::Sprite> load_from_spritesheet(const std::string load_settings_path, const sf::Texture& texture);

std::map<std::string, std::string> load_config(const std::string config_path, const char delimiter=':');


#endif