#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <iostream>
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
    window.setFramerateLimit(60);
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
        processEvents();
        //while(frameTime > timePerFrame) {
        //std::cout << (int)(1.f/frameTime.asSeconds()) << std::endl;
        //frameTime -= timePerFrame;
        //processEvents();
        update(sf::seconds(deltaTime));
        //}
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
        scene.handleEvent(event);
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
    deltaTime += ((0.01) * (sec - deltaTime));
}

int main()
{
    Game g;
    g.run();
    return 0;
}
