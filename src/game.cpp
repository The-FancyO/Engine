#include "../include/game.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

_game::_game():
    player(sf::Vector2f(200, 200)) {
    map_tex.loadFromFile("res/gfx/env/test.png");

    map.setSize(static_cast<sf::Vector2f>(map_tex.getSize()));
    map.setTexture(&map_tex);
    map.setPosition(0, 0); 
}
_game::~_game() {
    // Clean up dynamically allocated entities
    for (auto entity : entities) {
        delete entity; // Free memory for each entity
    }
}

void _game::poll_events(sf::RenderWindow &_window) {
    // Process events
    sf::Event event;
    while (_window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed)
            _window.close();

        player.poll_events();
    }
}

void _game::update(float _dt) { 
    player.update(_dt);

    handle_collisions(); // core function for collisions

    for (auto& i_entity : entities) {  // Update other entities (if any)
        i_entity->update(_dt);
    }
}

void _game::render(sf::RenderWindow &_window) {
    _window.draw(map);

    for (auto& i_entity : entities) { // Use non-const reference
        i_entity->render(_window);
    }

    player.render(_window);
}

void _game::handle_collisions() {
    // Get the player's bounding box and current position
    sf::FloatRect playerBounds = player.get_bounds();
    sf::Vector2f newPos = player.get_pos(); // Store the new position
    sf::Vector2f velocity = player.get_vel(); // Get the player's current velocity

    // Calculate the tile boundaries once
    int left_tile = std::max(0, static_cast<int>(playerBounds.left) / 48);
    int right_tile = std::min(8, static_cast<int>(playerBounds.left + playerBounds.width) / 48);
    int top_tile = std::max(0, static_cast<int>(playerBounds.top) / 48);
    int bottom_tile = std::min(9, static_cast<int>(playerBounds.top + playerBounds.height) / 48);

    // Iterate over the tiles in the bounding box around the player
    for (int i = left_tile; i <= right_tile; i++) {
        for (int j = top_tile; j <= bottom_tile; j++) {
            // If the tile is solid (tile value is 1)
            if (tile_map[j][i] == 1) {
                // Get the tile's bounding box
                sf::FloatRect tileBounds(i * 48, j * 48, 48, 48);

                // Check for collision
                if (playerBounds.intersects(tileBounds)) {
                    // Calculate the overlap in all directions
                    float overlapLeft = playerBounds.left + playerBounds.width - tileBounds.left;
                    float overlapRight = tileBounds.left + tileBounds.width - playerBounds.left;
                    float overlapTop = playerBounds.top + playerBounds.height - tileBounds.top;
                    float overlapBottom = tileBounds.top + tileBounds.height - playerBounds.top;

                    // Determine the minimum overlap
                    float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

                    // Resolve the collision based on the minimum overlap
                    if (minOverlap == overlapLeft) {
                        // Collision on the left
                        newPos.x = tileBounds.left - playerBounds.width; // Move player to the left of the tile
                    } else if (minOverlap == overlapRight) {
                        // Collision on the right
                        newPos.x = tileBounds.left + tileBounds.width; // Move player to the right of the tile
                    } else if (minOverlap == overlapTop) {
                        // Collision on the top
                        newPos.y = tileBounds.top - playerBounds.height; // Move player above the tile
                    } else if (minOverlap == overlapBottom) {
                        // Collision on the bottom
                        newPos.y = tileBounds.top + tileBounds.height; // Move player below the tile
                    }
                }
            }
        }
    }

    // Update the player's position based on collision resolution
    player.set_pos(newPos);
}
