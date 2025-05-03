#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Components/ComponentDefinitions.h"
#include "Entities/Entities.h"

void renderingThread(sf::RenderWindow *window, World *world) {
    // Activate window context
    static_cast<void>(window->setActive(true));

    // Rendering loop
    while (window->isOpen()) {
        // Clear buffer
        window->clear();

        // Draw level components

        // Draw plants
        for (const auto &drawable : world->getPlantDrawables())
            window->draw(*drawable);

        // Draw zombies
        for (const auto &drawable : world->getZombieDrawables())
            window->draw(*drawable);

        // Draw projectiles
        for (const auto &drawable : world->getProjectileDrawables())
            window->draw(*drawable);

        // Draw UI elements

        // End frame, display
        window->display();
    }
}

int main() {
    // Instantiate a clock
    auto clock = sf::Clock();

    // Create the window, must be done in the main loop
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Shooting Food at People with Dietary Issues");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // Deactivate its OpenGL context
    static_cast<void>(window.setActive(false));

    // Instantiate a new world
    auto world = World();

    /* EXAMPLE: Add entities */
    world.addPlant(sugarCubePlant({0, 0}));
    world.addZombie(diabeticZombie({500, 0}));

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &world);

    int i = 0;

    // Game loop
    while (window.isOpen()) {

        // Get time of last frame processing
        auto elapsed = clock.restart();

        // Quick polling
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Mouse
        auto mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
        const auto mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // Game processing
        world.update(elapsed.asSeconds(), mouse_position, mouse_pressed);

        std::cout << ++i << std::endl;

    }

    thread.join();
}
