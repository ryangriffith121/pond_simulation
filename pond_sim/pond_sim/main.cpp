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

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;


int main() {
    sf::RenderWindow window(sf::VideoMode({ 800u, 800u }), "Pond Simulation");
    window.setFramerateLimit(60);

    sf::Clock clock;

    Pond pond1 = Pond{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

    pond1.addFish(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, "Paco", 100, { 240, 240, 255 });

    while (window.isOpen()) {

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        pond1.update(dt);

        window.clear(sf::Color(50, 50, 70));
        
        pond1.draw(dt);

        window.display();
    }

    return 0;
}