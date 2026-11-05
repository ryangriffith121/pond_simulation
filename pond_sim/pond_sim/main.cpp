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

int main()
{
    // --- Window ---
    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "SFML Basics");
    window.setFramerateLimit(60);

    // --- Shapes ---
    sf::CircleShape player(30.f);
    player.setFillColor(sf::Color::Cyan);
    player.setOrigin({ 30.f, 30.f });          // origin at center
    player.setPosition({ 400.f, 300.f });

    sf::RectangleShape box({ 120.f, 80.f });
    box.setFillColor(sf::Color(255, 120, 0));
    box.setOutlineColor(sf::Color::White);
    box.setOutlineThickness(3.f);
    box.setPosition({ 100.f, 100.f });

    // --- Text (needs a font file next to the executable) ---
    sf::Font font;
    bool hasFont = font.openFromFile("arial.ttf");   // change to any .ttf you have
    sf::Text label(font, "", 20);
    label.setPosition({ 10.f, 10.f });

    sf::Clock clock;
    const float speed = 250.f;               // pixels per second
    bool followMouse = false;

    while (window.isOpen())
    {
        // --- Events ---
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                    window.close();
                if (key->code == sf::Keyboard::Key::Space)
                    followMouse = !followMouse;
            }

            if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (click->button == sf::Mouse::Button::Left)
                    box.setPosition(sf::Vector2f(click->position));   // move box to click
            }
        }

        // --- Update ---
        float dt = clock.restart().asSeconds();
        sf::Vector2f move(0.f, 0.f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) move.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) move.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) move.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) move.x += 1.f;

        player.move(move * speed * dt);
        player.rotate(sf::degrees(90.f * dt));

        if (followMouse)
            player.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)));

        // Collision: change color when the player's bounds touch the box
        if (player.getGlobalBounds().findIntersection(box.getGlobalBounds()))
            player.setFillColor(sf::Color::Red);
        else
            player.setFillColor(sf::Color::Cyan);

        if (hasFont)
        {
            label.setString("WASD: move | Space: follow mouse | Click: move box | Esc: quit\nFPS: "
                + std::to_string(static_cast<int>(1.f / dt)));
        }

        // --- Draw ---
        window.clear(sf::Color(20, 20, 30));
        window.draw(box);
        window.draw(player);
        if (hasFont) window.draw(label);
        window.display();
    }

    return 0;
}