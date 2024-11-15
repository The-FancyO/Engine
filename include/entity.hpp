#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#ifndef ENTITY_CLASS
#define ENTITY_CLASS

class _entity {
public:
    std::string id;

    _entity(std::string _id, sf::Vector2f _pos, sf::Vector2f _size, float _angle);
    virtual ~_entity();

    virtual void update(float _dt);
    virtual void render(sf::RenderWindow &_window);

private:
    sf::RectangleShape rect;
};

#endif // !ENTITY_CLASS
