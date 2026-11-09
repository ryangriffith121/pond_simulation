#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <cmath>
#include <cstdint>
#include <random>

#include <SFML/Graphics.hpp>

#include "fish.h"
#include "pond.h"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;


int main() {
    sf::RenderWindow window(sf::VideoMode({ static_cast<unsigned>(WINDOW_WIDTH), static_cast<unsigned>(WINDOW_HEIGHT) }), "Pond Simulation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Pond pond1 = Pond{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    pond1.addFish(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 3, "Paco", 150, { 230, 230, 245 });
    pond1.addFish(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, "Pico", 125, { 245, 230, 225 });
    pond1.addFish(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "Goob", 100, { 245, 230, 215 });
    pond1.addFish(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, "Glib", 110, { 230, 230, 215 });
    pond1.addFish(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3, "Glob", 125, { 245, 245, 215 });
    pond1.addFish(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, "Gleeb", 160, { 215, 210, 215 });
    pond1.addFish(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4, "Clyde", 130, { 235, 240, 215 });

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        pond1.update(dt);

        window.clear(sf::Color(100, 140, 200));

        pond1.draw(dt, window);

        window.display();
    }

    return 0;
}
