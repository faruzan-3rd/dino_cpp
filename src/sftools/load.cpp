#include <sftools/assets/load.hpp>
#include <sftools/str/strman.hpp>
#include <fstream>
#include <iostream>
#include <stdio.h>


std::map<std::string, sf::Sprite> load_from_spritesheet(const std::string load_settings_path, const sf::Texture& texture){
    std::map<std::string, std::string> loaded_cfg = load_config(load_settings_path);
    std::map<std::string, sf::Sprite> ret;

    int line{1};
    for(auto it = loaded_cfg.begin(); it != loaded_cfg.end(); it++){
        std::vector<std::string> rect_spl;
        int rect[4];
        split_str(it->second, ',', rect_spl);
        if(rect_spl.size() < 2){
            std::cout << "Bad format (sprite) at line " << line << " returning " << std::endl;
            return ret;
        }
        for(int i = 0; i < 4; i++) rect[i] = std::stoi(rect_spl[i]);

        sf::IntRect rct(rect[0], rect[1], rect[2], rect[3]);
        sf::Sprite spr = sf::Sprite(texture, rct);
        ret[it->first] = spr;
        line++;
    }

    return ret;
}


std::map<std::string, std::string> load_config(const std::string config_path, const char delimiter){
    std::ifstream ifs;
    ifs.open(config_path);
    std::string line;
    std::map<std::string, std::string> ret;
    int line_num{1};

    while(getline(ifs, line)){
        if(*(line.end() - 1) == '\n') line.erase(line.end() - 1);

        std::vector<std::string> spl;
        split_str(line, delimiter, spl);
        if(spl.size() < 2){
            std::cout << "Bad format (cfg) at line " << line_num << " returning " << std::endl;
            ifs.close();
            return ret;
        }

        ret[spl[0]] = spl[1];
    }

    ifs.close();
    return ret;

}