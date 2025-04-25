#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>



void renderingThread(sf::RenderWindow *window) {
    // Activate window context
    window->setActive(true);

    // Rendering loop
    while (window->isOpen()) {
        // Clear buffer
        window->clear(sf::Color::Black);

        // Draw level components
        // Draw plants (VERTEX ARRAY)
        // Draw zombies (VERTEX ARRAY)
        // Draw projectiles (VERTEX ARRAY)
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
    // Create the window, must be done in the main loop
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "OpenGL");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // Deactivate its OpenGL context
    window.setActive(false);

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window);

    // Game loop
    while (window.isOpen()) {
        // Handle events!
        handleEvents(window);

        // Handle events!
    }

    thread.join();
}
