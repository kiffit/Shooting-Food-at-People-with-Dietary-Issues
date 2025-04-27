#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GameController.h"
#include "Entities/Plants/Peashooter.h"
#include "Entities/Zombies/RegularJoe.h"

void renderingThread(sf::RenderWindow *window, GameController *controller, sf::Text *text) {
    // Activate window context
    static_cast<void>(window->setActive(true));

    // Rendering loop
    while (window->isOpen()) {
        // Clear buffer
        window->clear(sf::Color::Black);

        // Copy front buffers of entities for rendering
        std::vector<std::shared_ptr<Entity>> plants;
        std::vector<std::shared_ptr<Entity>> zombies;
        std::vector<std::shared_ptr<Entity>> projectiles;
        {
            std::scoped_lock lock(controller->mutex_lock);
            plants = controller->plants_front;
            zombies = controller->zombies_front;
            projectiles = controller->projectiles_front;
        }

        // Render each snapshot


        // Draw level components

        // Draw plants (VERTEX ARRAY?)
        for (const auto &plant: plants) {
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
        for (const auto &plant: zombies) {
            // Draw rectangle of plant
            auto renderRectangle = sf::RectangleShape(plant->get_hitbox().size);
            renderRectangle.setPosition(plant->get_hitbox().position);
            window->draw(renderRectangle);

            // Draw text for that bad boy
            text->setString(plant->debug_string());
            text->setPosition(plant->get_hitbox().position);
            window->draw(*text);
        }

        // Draw projectiles (VERTEX ARRAY?)
        for (const auto &plant: projectiles) {
            // Draw rectangle of plant
            auto renderRectangle = sf::RectangleShape(plant->get_hitbox().size);
            renderRectangle.setPosition(plant->get_hitbox().position);
            window->draw(renderRectangle);

            // Draw text for that bad boy
            text->setString(plant->debug_string());
            text->setPosition(plant->get_hitbox().position);
            window->draw(*text);
        }

        // Draw UI elements

        // End frame, display
        window->display();
    }
}

void handleEvents(sf::RenderWindow &window, GameController &gc) {
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
                gc.cleanup();
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
    for (int i = 0; i < 5; i++) {
        gc.plants_back.push_back(std::make_shared<Peashooter>(sf::Vector2f(0, 110) * static_cast<float>(i)));
        gc.zombies_back.push_back(std::make_shared<RegularJoe>(sf::Vector2f(200, 0) + sf::Vector2f(50, 110) * static_cast<float>(i)));
    }

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &gc, &text);

    // Game loop
    while (window.isOpen()) {
        // Get time of last frame processing
        auto elapsed = clock.restart();

        // Handle events, including inputs
        handleEvents(window, gc);

        // Game processing
        gc.update(elapsed);

        std::cout << "Physics Frame for [" << gc.projectiles_front.size() + gc.zombies_front.size() + gc.plants_front.size() << "] entities: " << elapsed.asSeconds() << std::endl;
    }

    thread.join();
}
