#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <ctime>
#include <iostream>

#include "../include/game.hpp"

int main() {
    std::cout<<"Game Starting"<<"\n";

    const int screen_width = 1280;
    const int screen_height = 720;

    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Amorphous");

    _game game;

    window.setFramerateLimit(60);

    while (window.isOpen()) {
        float _dt = clock.restart().asSeconds();

        game.poll_events(window);

        game.update(_dt);

        window.clear(); 
        game.render(window);
        window.display();
    }

    return 0;
}
