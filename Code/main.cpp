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
    const auto backgroundTexture = sf::Texture("../Design/Sprites/map.png");
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
            window->draw(*drawable, &shader);

        // Draw UI elements
        for (const auto &drawable: world->getShopItemDrawables())
            window->draw(*drawable, &shader);

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

    // Make the world store
    auto epipen_plant_store = epipenPlantStore({0, 900});
    auto soy_minigun_plant_store = soybeanMinigunPlantStore({100, 900});
    auto baguette_launcher_plant_store = baguetteStore({200, 900});
    auto milk_store = milkStore({300, 900});
    auto peanut_store = peanutStore({400, 900});
    // auto pistol_plant = pistolStore({500, 900});

    world.addShopItem(epipen_plant_store);
    world.addShopItem(soy_minigun_plant_store);
    world.addShopItem(baguette_launcher_plant_store);
    world.addShopItem(milk_store);
    world.addShopItem(peanut_store);

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &world);

    int i = 0;
    float sun_time = 0;
    float z = 0;

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

        // TEMP: Zombie apocalypse
        z += elapsed.asSeconds();
        if (z >= 1) {
            world.addZombie(glutenZombie({static_cast<float>(std::rand() % 5) * 100 + 1800, static_cast<float>(std::rand() % 9) * 100}));
            world.addZombie(soyZombie({static_cast<float>(std::rand() % 5) * 100 + 1800, static_cast<float>(std::rand() % 9) * 100}));
            world.addZombie(milkZombie({static_cast<float>(std::rand() % 5) * 100 + 1800, static_cast<float>(std::rand() % 9) * 100}));
            world.addZombie(peanutZombie({static_cast<float>(std::rand() % 5) * 100 + 1800, static_cast<float>(std::rand() % 9) * 100}));
            z = 0;
        }

        // Add random sun
        sun_time += elapsed.asSeconds();
        if (sun_time >= 80) {
            world.addProjectile(epipenProjectile({static_cast<float>(std::rand() % 18) * 100, static_cast<float>(std::rand() % 9) * 100}));
            sun_time = 0;
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
