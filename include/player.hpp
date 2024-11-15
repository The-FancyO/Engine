#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#ifndef PLAYER_CLASS
#define PLAYER_CLASS

class _player {
public:
    _player(sf::Vector2f _pos);
    ~_player();

    void poll_events();
    void update(float _dt);
    void render(sf::RenderWindow &_window);

    sf::Vector2f get_pos();
    sf::Vector2f get_size();
    sf::Vector2f get_vel();
    sf::FloatRect get_bounds();

    void set_pos(sf::Vector2f new_pos);
    void set_size(sf::Vector2f new_size);
    void set_vel(sf::Vector2f new_vel);

private:
    sf::Vector2f pos; 
    sf::Vector2f size;

    float speed;
    sf::Vector2f vel;

    sf::RectangleShape rect;
};

#endif // !PLAYER_CLASS
