#include "../include/entity.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

_entity::_entity(std::string _id, sf::Vector2f _pos, sf::Vector2f _size, float _angle) {
    id = _id;

    rect.setSize(_size);
    rect.setRotation(_angle);
    rect.setPosition(_pos);
    rect.setFillColor(sf::Color::White);
}

_entity::~_entity() { }

void _entity::update(float _dt) { 
    rect.rotate(25.0f);
}

void _entity::render(sf::RenderWindow &_window) {
    _window.draw(rect);
}
