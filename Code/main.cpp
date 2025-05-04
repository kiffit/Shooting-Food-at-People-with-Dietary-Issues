#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Entities/Entities.h"

void renderingThread(sf::RenderWindow *window, World *world) {
    // Activate window context
    static_cast<void>(window->setActive(true));

    // Bobbing shader
    sf::Shader shader;
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    constexpr std::string_view fragmentShader = R"(
    uniform sampler2D texture;
    uniform float time;

    void main()
    {
        // Base texture coordinate
        vec2 uv = gl_TexCoord[0].xy;

        // X, Y axis factor
        float xfactor = clamp(1 - uv.y, 0, 1) / 10;
        float yfactor = clamp(1 - uv.y, 0, 1) / 5;

        // Optional time-based modulation for dynamic effect
        float xwobble = cos(time);
        float ywobble = abs(sin(time));

        // Shear: shift X coordinate based on Y
        uv.x += xwobble * xfactor;
        uv.y += ywobble * yfactor;

        // Sample texture and modulate by vertex color
        vec4 pixel = texture2D(texture, uv);
        gl_FragColor = gl_Color * pixel;
    })";


    if (!shader.loadFromMemory(fragmentShader, sf::Shader::Type::Fragment))
        std::cout << "Shader failed to load!" << std::endl;

    // Background
    const auto backgroundTexture = sf::Texture("../Code/Entities/Sprites/map.png");
    const auto background = sf::Sprite(backgroundTexture);

    // Rendering loop
    while (window->isOpen()) {
        // Clear buffer
        window->clear(sf::Color::Black);

        // Draw background
        window->draw(background);

        // Draw level components
        shader.setUniform("time", world->time);

        // Draw plants
        for (const auto &drawable: world->getPlantDrawables())
            window->draw(*drawable, &shader);

        // Draw zombies
        for (const auto &drawable: world->getZombieDrawables())
            window->draw(*drawable);

        // Draw projectiles
        for (const auto &drawable: world->getProjectileDrawables())
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
    window.setFramerateLimit(165);
    window.setKeyRepeatEnabled(false);

    // Deactivate its OpenGL context
    static_cast<void>(window.setActive(false));

    // Instantiate a new world
    auto world = World();

    /* EXAMPLE: Add entities */
    for (int x = 0; x < 9; ++x) {
        world.addPlant(epipenPlant({200, 100.0f * x}));
        world.addPlant(baguettePlant({100, 100.0f * x}));
        world.addPlant(soybeanMinigunPlant({0, 100.0f * x}));
        world.addZombie(soyZombie({500 + 100.0f * x, 100.0f * x}));
        world.addZombie(glutenZombie({700 + 100.0f * x, 100.0f * x}));
    }

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &world);

    int i = 0;

    // Game loop
    while (window.isOpen()) {
        // Get time of last frame processing
        auto elapsed = clock.restart();

        // Quick polling
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Mouse
        auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        const auto mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // Game processing
        world.update(elapsed.asSeconds(), mouse_position, mouse_pressed);

        std::cout << ++i << std::endl;
    }

    thread.join();
}
