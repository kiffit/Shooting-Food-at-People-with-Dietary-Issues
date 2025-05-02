    #include <iostream>
    #include <thread>
    #include <SFML/Graphics.hpp>
    #include "World.h"
#include "Entities/Plants.h"

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

            // Draw projectiles

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
        auto world = World(&window);

        /* EXAMPLE: Add entities */
        auto normal = createRegularGuy();
        auto draggable = createDraggableGuy();
        auto draggable2 = createDraggableGuy();
        normal->position = {0, 0};
        draggable->velocity = {100, 100};
        draggable2->velocity = {200, 200};
        world.addPlant(normal);
        world.addPlant(draggable);
        world.addPlant(draggable2);

        for (int x = 0; x < 10; x++) {
            auto d = createDraggableGuy();
            d->velocity = {100.f * x, 100.f * x};
            world.addPlant(d);
        }

        // Launch the rendering thread
        std::thread thread(&renderingThread, &window, &world);

        int i = 0;

        // Game loop
        while (window.isOpen()) {
            // Get time of last frame processing
            auto elapsed = clock.restart();

            // Game processing
            world.update(elapsed.asSeconds());

            // Quick polling
            while (const std::optional event = window.pollEvent())
            {
                // "close requested" event: we close the window
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            std::cout << ++i << std::endl;

        }

        thread.join();
    }
