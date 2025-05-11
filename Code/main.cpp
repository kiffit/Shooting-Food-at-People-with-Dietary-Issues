#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "World.h"
#include "Entities/Entities.h"
#include "SFML/Audio/Music.hpp"

void renderingThread(sf::RenderWindow *window, World *world, std::vector<float> *epipenValues, std::vector<sf::Vector2f> *screenLocations) {
    // Activate window context
    static_cast<void>(window->setActive(true));

    // Bobbing shader
    sf::Shader shader;
    shader.setUniform("texture", sf::Shader::CurrentTexture);

    constexpr std::string_view fragmentShader = R"(
    #version 140
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
    const auto backgroundTexture = sf::Texture("../Design/Sprites/awesome_map.png");
    auto background = sf::Sprite(backgroundTexture);
    background.setScale({9.15, 9.15});

    // Font for UI
    sf::Font font("../Design/Sprites/font.ttf");

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

        // Draw UI text
        for (std::size_t i = 0; i < epipenValues->size(); ++i) {
            sf::Text text(font);
            text.setString(std::to_string(static_cast<int>(epipenValues->at(i))));
            text.setCharacterSize(40);
            text.setFillColor(sf::Color::White);
            text.setPosition(screenLocations->at(i));
            window->draw(text);
        }

        // Draw total epipens
        sf::Text text(font);
        text.setString(std::to_string(static_cast<int>(world->epipens)));
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::White);
        text.setPosition({650, 50});
        window->draw(text);
        text.setString("Epipens:");
        text.setPosition({650, 10});
        window->draw(text);

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

    // Init music
    sf::Music music("../Design/Sounds/depression.mp3");
    music.setLooping(true);
    music.play();

    // Instantiate a new world
    auto world = World();

    // Make the world store
    auto epipen_plant_store = epipenPlantStore({0, 0});
    auto soy_minigun_plant_store = soybeanMinigunPlantStore({100, 0});
    auto baguette_launcher_plant_store = baguetteStore({200, 0});
    auto milk_store = milkStore({300, 0});
    auto peanut_store = peanutStore({400, 0});
    auto gun_store = gunPlantStore({500, 0});

    world.addShopItem(epipen_plant_store);
    world.addShopItem(soy_minigun_plant_store);
    world.addShopItem(baguette_launcher_plant_store);
    world.addShopItem(milk_store);
    world.addShopItem(peanut_store);
    world.addShopItem(gun_store);

    // Interval for random sun to appear
    auto sun_interval = 4.f;

    /* KADE: Edit values here. */
    /*
     * Initial times: time pass before enemies start to spawn (seconds)
     * Global time scale: use to slow/speed up all spawns by a constant multiplier
     *
     */

    // When each zombie will begin having chances to spawn
    auto initial_gluten_zombie_time = 10.f;
    auto initial_soy_zombie_time = 120.f;
    auto initial_milk_zombie_time = 40.f;
    auto initial_peanut_zombie_time = 90.f;

    // Higher scale = higher spawn rates
    auto global_time_scale = 0.01f;
    auto gluten_zombie_time_scale = 1.f;
    auto soy_zombie_time_scale = 8.f;
    auto milk_zombie_time_scale = 3.f;
    auto peanut_zombie_time_scale = 6.f;

    // Timers to keep track
    auto game_timer = 0.f;
    auto sun_timer = 0.f;
    auto gluten_timer = 0.f;
    auto soy_timer = 0.f;
    auto milk_timer = 0.f;
    auto peanut_timer = 0.f;

    // Set epipen text data
    std::vector<float> epipenValues = world.getShopEpipenValues();
    std::vector<sf::Vector2f> positions = {
        {10, 20}, {110, 20}, {210, 20}, {310, 20}, {410, 20}, {510, 20}
    };

    // Launch the rendering thread
    std::thread thread(&renderingThread, &window, &world, &epipenValues, &positions);

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

        // Adjust timers
        auto seconds = elapsed.asSeconds();
        game_timer += seconds;
        sun_timer += seconds;
        gluten_timer += seconds;
        soy_timer += seconds;
        milk_timer += seconds;
        peanut_timer += seconds;

        // Random sun
        if (sun_timer > sun_interval) {
            sun_timer = 0;
            world.addProjectile(epipenProjectile({
                static_cast<float>(std::rand() % 17) * 100, static_cast<float>(std::rand() % 9) * 100 + 100
            }));
        }

        if (game_timer > initial_gluten_zombie_time && gluten_timer > std::max(
                1.f, gluten_zombie_time_scale / ((game_timer - initial_gluten_zombie_time) * global_time_scale))) {
            gluten_timer = 0;
            world.addZombie(glutenZombie({
                static_cast<float>(std::rand() % 2) * 87 + 2000,
                100 + static_cast<float>(std::rand() % 9) * 110 - 20
            }));
        }

        if (game_timer > initial_soy_zombie_time &&
            soy_timer > std::max(1.f, soy_zombie_time_scale /
                                      ((game_timer - initial_soy_zombie_time) * global_time_scale))) {
            soy_timer = 0;
            world.addZombie(soyZombie({
                static_cast<float>(std::rand() % 2) * 87 + 2000,
                100 + static_cast<float>(std::rand() % 9) * 110 - 20
            }));
        }

        if (game_timer > initial_milk_zombie_time &&
            milk_timer > std::max(1.f, milk_zombie_time_scale /
                                       ((game_timer - initial_milk_zombie_time) * global_time_scale))) {
            milk_timer = 0;
            world.addZombie(milkZombie({
                static_cast<float>(std::rand() % 2) * 87 + 2000,
                100 + static_cast<float>(std::rand() % 9) * 110 - 20
            }));
        }

        if (game_timer > initial_peanut_zombie_time &&
            peanut_timer > std::max(1.f, peanut_zombie_time_scale /
                                         ((game_timer - initial_peanut_zombie_time) * global_time_scale))) {
            peanut_timer = 0;
            world.addZombie(peanutZombie({
                static_cast<float>(std::rand() % 2) * 87 + 2000,
                100 + static_cast<float>(std::rand() % 9) * 110 - 20
            }));
        }

        // Mouse
        auto mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        const auto mouse_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

        // Game processing
        world.update(elapsed.asSeconds(), mouse_position, mouse_pressed);

        // Are we cooked chat
        if (world.areWeCookedChat())
            window.close();
    }

    thread.join();
}
