#pragma once

#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>

#ifndef GAME_CLASS
#define GAME_CLASS

class _game {
public:
    _game();
    ~_game();

    void poll_events(sf::RenderWindow &_window);

    void update(float _dt);
    void render(sf::RenderWindow &_window);

private:
    _player player;

    sf::Texture map_tex;

    sf::RectangleShape map;

    int tile_map[9][8] = {
        {1,1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1},
        {1,1,1,0,0,1,1,1},
        {1,1,1,0,0,1,1,1},
        {1,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,1},
        {1,1,1,0,0,1,1,1}
    };

    std::vector<_entity*> entities; // Use raw pointers for simplicity
    
    void handle_collisions();
};

#endif // !GAME_CLASS
