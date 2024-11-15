#include "../include/player.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Joystick.hpp>
#include <cmath>

_player::_player(sf::Vector2f _pos) {
    pos = _pos;
    size = sf::Vector2f(48, 48);

    speed = 300.0f;
    vel = sf::Vector2f(0.0f, 0.0f);

    rect.setPosition(pos);
    rect.setSize(size);
    rect.setRotation(0.0f);
    rect.setFillColor(sf::Color::Yellow);
}

_player::~_player() { }

void _player::poll_events() {
    const float DEAD_ZONE = 20.0f;  // Adjust as needed for joystick dead zone

    float stick_x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
    float stick_y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

    // Dead zone filtering
    if (std::abs(stick_x) < DEAD_ZONE) stick_x = 0.0f;
    if (std::abs(stick_y) < DEAD_ZONE) stick_y = 0.0f;

    vel = sf::Vector2f(0.0f, 0.0f); // Reset velocity

    // Handle keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || stick_y < -50) {
        vel.y -= 1.0f;  // Move up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || stick_y > 50) {
        vel.y += 1.0f;  // Move down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || stick_x > 50) {
        vel.x += 1.0f;  // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || stick_x < -50) {
        vel.x -= 1.0f;  // Move left
    }

    // Normalize the velocity vector if it's not zero
    if (vel.x != 0.0f || vel.y != 0.0f) {
        float length = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        vel.x /= length;
        vel.y /= length;
    }

    // Apply the desired speed after normalization
    vel *= speed;  // Set the speed after normalizing the direction
}

void _player::update(float _dt) {
    // Update position based on velocity and delta time
    pos += vel * _dt;

    // Update the rectangle position to reflect the player position
    rect.setPosition(pos);
}

void _player::render(sf::RenderWindow &_window) {
    _window.draw(rect);
}

sf::Vector2f _player::get_pos() { return rect.getPosition(); }
sf::Vector2f _player::get_size() { return rect.getSize(); }
sf::Vector2f _player::get_vel() { return vel; }
sf::FloatRect _player::get_bounds() { return rect.getGlobalBounds(); }

void _player::set_pos(sf::Vector2f new_pos) {
    pos = new_pos;
    rect.setPosition(new_pos);
}

void _player::set_size(sf::Vector2f new_size) {
    size = new_size;
    rect.setSize(new_size);
}

void _player::set_vel(sf::Vector2f new_vel) {
    vel = new_vel;
}
