#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include "Entities/Plants/Peashooter.h"

void renderingThread(sf::RenderWindow *window, const GameController *controller, sf::Text *text) {
    // Activate window context
    static_cast<void>(window->setActive(true));

    // Rendering loop
    while (window->isOpen()) {
        // Clear buffer
        window->clear(sf::Color::Black);

        // Draw level components

        // Draw plants (VERTEX ARRAY?)
        for (const auto &plant: controller->plants) {
            // Draw rectangle of plant
            auto renderRectangle = sf::RectangleShape(plant->get_hitbox().size);
            renderRectangle.setPosition(plant->get_hitbox().position);
            window->draw(renderRectangle);

            // Draw text for that bad boy
            text->setString(plant->debug_string());
            text->setPosition(plant->get_hitbox().position);
            window->draw(*text);
        }

        // Draw zombies (VERTEX ARRAY?)

        // Draw projectiles (VERTEX ARRAY?)

        // Draw UI elements

        // End frame, display
        window->display();
    }
}

void handleEvents(sf::RenderWindow &window) {
    while (const auto event = window.pollEvent()) {
        // Handle close events
        if (event->is<sf::Event::Closed>())
            window.close();

        // Handle input presses
        if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            // Close window... may wish to show pause menu
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();

            if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                std::cout << "space in" << std::endl;
        }

        // Handle input releases
        if (const auto keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->scancode == sf::Keyboard::Scancode::Space)
                std::cout << "space out" << std::endl;
        }
    }
}

int main() {
    // Instantiate a GameController
    auto gc = GameController();

    // Instantiate a clock
    auto clock = sf::Clock();

    // Create the window, must be done in the main loop
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Shooting Food at People with Dietary Issues");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // Deactivate its OpenGL context
    static_cast<void>(window.setActive(false));

    /* OLD: TEXT INSTANTIATION */
    const sf::Font font("Arial.ttf");
    sf::Text text(font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::Black);

    /* OLD: MAKE A LOT OF ENTITIES */
    for (int i = 0; i < 200; i++) {
        gc.plants.push_back(std::make_shared<Peashooter>(sf::Vector2f(100, 100) * static_cast<float>(i)));
    }

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &gc, &text);

    // Game loop
    while (window.isOpen()) {
        // Get time of last frame processing
        auto elapsed = clock.restart();

        // Handle events, including inputs
        handleEvents(window);

        // Game processing
        gc.update(elapsed);
    }

    thread.join();
}
