#include <sftools/collision/collision.hpp>



bool is_colliding(const sf::Vector2f& box1_origin, const sf::Vector2f& box1_dimension, const sf::Vector2f& box2_origin, const sf::Vector2f& box2_dimension){
    float box1_horizontal_left = box1_origin.x, box1_horizontal_right = box1_origin.x + box1_dimension.x;
    float box1_vertical_top = box1_origin.y, box1_vertical_bottom = box1_origin.y + box1_dimension.y;
    float box2_horizontal_left = box2_origin.x, box2_horizontal_right = box2_origin.x + box2_dimension.x;
    float box2_vertical_top = box2_origin.y, box2_vertical_bottom = box2_origin.y + box2_dimension.y;

    bool horizontal_overlap = (box1_horizontal_left <= box2_horizontal_left && box2_horizontal_left <= box1_horizontal_right) || (box1_horizontal_left <= box2_horizontal_right && box2_horizontal_right <= box1_horizontal_right);
    bool vertical_overlap = (box1_vertical_top <= box2_vertical_top && box2_vertical_top <= box1_vertical_bottom) || (box1_vertical_top <= box2_vertical_bottom && box2_vertical_bottom <= box1_vertical_bottom);

    return horizontal_overlap && vertical_overlap;
}
