#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include "TileMap.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include "Game.hpp"
#include "Icon.hpp"
#include <cassert>

using namespace std;

Game::Game() : window(sf::VideoMode(1200, 675), sf::String(L"SFMetroid")),
               scene(window),
               deltaTime(FRAME_RATE)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(65);
    window.setIcon(game_icon.width, game_icon.height, game_icon.pixel_data);
}

void Game::run()
{
    sf::Clock frameClock;
    sf::Music music;
    assert(music.openFromFile(WORLD_MUSIC_FILE_PATH));
    music.setLoop(true);
    music.play();
    while (window.isOpen())
    {
        frameAverage(frameClock.restart());

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code == sf::Keyboard::R)
            {
                scene.reset();
                music.stop();
                music.play();
                deltaTime = FRAME_RATE;
            }
            scene.handleEvent(event);
        }

        update(sf::seconds(deltaTime));
        render();
    }
}

void Game::update(const sf::Time &frameTime)
{
    scene.update(frameTime);
}

void Game::render()
{
    window.clear();
    scene.draw();
    window.display();
}

void Game::frameAverage(const sf::Time &time)
{
    float sec = time.asSeconds();
    deltaTime += ((0.0125) * (sec - deltaTime));
}

int main()
{
    Game g;
    g.run();
    return 0;
}
