#include <SFML/Graphics.hpp>
#include <cassert>

#include "Scene.hpp"

Scene::Scene(sf::RenderWindow &window) : player(*this, playerTexture, sf::Vector2f(320.f, 260.f)),
                                         tileMap(mapTexture),
                                         parentWindow(window),
                                         mainView(sf::Vector2f(0.f, 0.f), sf::Vector2f(320.f, 180.f)),
                                         beamList(),
                                         zList(),
                                         gameOverText("GAME OVER", font),
                                         restartText("Press r to restart the game", font)
{
    assert(mapTexture.loadFromFile(TILESET_FILE_PATH));
    assert(playerTexture.loadFromFile(PLAYER_TEXTURE_FILE_PATH));
    assert(font.loadFromFile(HUD_FONT));
    assert(enemiesTexture.loadFromFile(ENEMIES_TEXTURE_FILE_PATH));

    gameOverText.setCharacterSize(30);
    restartText.setCharacterSize(14);
    gameOverText.setPosition(-120, -30);
    restartText.setPosition(-110, 30);
    hud = HUD(font);
    changeLevel(0);

    sf::Vector2f center = player.getPosition();
    center.x += 20.f;
    center.y -= 20.f;
    mainView.setCenter(center);
    window.setView(mainView);
}

void Scene::draw()
{
    if (player.isDead)
    {
        parentWindow.draw(gameOverText);
        parentWindow.draw(restartText);
        return;
    }
    parentWindow.draw(tileMap);
    parentWindow.draw(player);
    for (const Beam &b : beamList)
    {
        parentWindow.draw(b);
    }
    for (const Zoomer &z : zList)
    {
        parentWindow.draw(z);
    }

    parentWindow.draw(hud);
}

void Scene::handleEvent(const sf::Event &evt)
{
    sf::Keyboard::Key key = evt.key.code;
    bool isPressed = evt.type == sf::Event::KeyPressed;

    if (key == sf::Keyboard::Z)
        player.jumpPressed = isPressed;
    else if (key == sf::Keyboard::Q)
        player.leftPressed = isPressed;
    else if (key == sf::Keyboard::S)
        player.downPressed = isPressed;
    else if (key == sf::Keyboard::D)
        player.rightPressed = isPressed;
    else if (key == sf::Keyboard::Space)
        player.firePressed = isPressed;
    else if (isPressed && key == sf::Keyboard::Escape)
        parentWindow.close();
}

void Scene::update(const sf::Time &frameTime)
{
    if (player.isDead)
    {
        mainView.setCenter(0.f, 0.f);
        parentWindow.setView(mainView);
        return;
    }

    sf::Vector2f pMove;
    int trigger = 0;

    //Update Beam list
    for (auto it = beamList.begin(); it != beamList.end(); ++it)
    {
        it->update(frameTime);
        pMove = it->movement * frameTime.asSeconds();
        if (tileMap.computeCollision(it->getGlobalBounds(), pMove, trigger) || !it->move(pMove))
            it = beamList.erase(it);
    }

    trigger = 0;

    //Update Zoomer list
    for (auto it = zList.begin(); it != zList.end(); ++it)
    {
        sf::FloatRect bounds = it->getGlobalBounds();
        it->update(frameTime);
        pMove = it->movement * frameTime.asSeconds();
        it->move(pMove);
        for (auto b = beamList.begin(); b != beamList.end(); ++b)
        {
            if (bounds.intersects(b->getGlobalBounds()))
            {
                it = zList.erase(it);
                b = beamList.erase(b);
            }
        }
        if (bounds.intersects(player.getGlobalBounds()))
        {
            player.dealDamage(16.f);
        }
    }

    player.update(frameTime);

    //Update player position
    if (abs(player.movement.x) > 0.1f || abs(player.movement.y) > 0.1f)
    {
        //Player collision
        pMove = player.movement * frameTime.asSeconds();
        tileMap.computeCollision(player.getGlobalBounds(), pMove, trigger);
        if (trigger != 0)
        {
            changeLevel(trigger);
        }

        player.landing(pMove);
        player.move(pMove);

        //Move camera
        float halfX = mainView.getSize().x / 2.f;
        float halfY = mainView.getSize().y / 2.f;
        sf::Vector2f center = player.getPosition();
        if (!((player.getPosition().x < tileMap.mapPixelSize.x - halfX) && (player.getPosition().x > halfX)))
            center.x = mainView.getCenter().x;
        if (!((player.getPosition().y < tileMap.mapPixelSize.y - halfY) && (player.getPosition().y > halfY)))
            center.y = mainView.getCenter().y;

        mainView.setCenter(center);
    }

    if (player.isDamaged)
        hud.sethealth(player.health);
    hud.update(frameTime);
    hud.setPosition(mainView.getCenter().x + 155.f, mainView.getCenter().y - 90.f);
    parentWindow.setView(mainView);
}

void Scene::addBeamShot(const sf::Vector2f &position, bool facingRight)
{
    Beam b = Beam(*this, position, playerTexture, facingRight);
    beamList.push_front(b);
}

void Scene::changeLevel(int trigger)
{
    int level;
    sf::Vector2f pos;
    zList.clear();
    beamList.clear();

    switch (trigger)
    {
    case -2:
        level = 2;
        pos = std::move(sf::Vector2f(45.f, 710.f));
        break;
    case -3:
        level = 1;
        pos = std::move(sf::Vector2f(580.f, 300.f));
        break;
    case -4:
        level = 3;
        pos = std::move(sf::Vector2f(48.f, 55.f));
        break;
    case -5:
        level = 3;
        pos = std::move(sf::Vector2f(730.f, 230.f));
        break;
    case -6:
        level = 2;
        pos = std::move(sf::Vector2f(48.f, 110.f));
        break;
    case -7:
        level = 2;
        pos = std::move(sf::Vector2f(340.f, 90.f));
        break;
    default:
        level = 1;
        pos = std::move(sf::Vector2f(320.f, 300.f));
        break;
    }

    switch (level)
    {
    case 1:
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(384.f, 128.f), 80));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(96.f, 320.f), 64));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(112.f, 240.f), 80));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(528.f, 304.f), 40));
        break;
    case 2:
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(272.f, 720.f), 64));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(272.f, 528.f), 64));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(144.f, 496.f), 96));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(192.f, 352.f), 80));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(144.f, 128.f), 64));
        break;

    case 3:
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(192.f, 240.f), 64));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(432.f, 240.f), 64));
        zList.push_back(Zoomer(enemiesTexture, sf::Vector2f(528.f, 128.f), 64));
        break;

    default:
        break;
    }

    tileMap.loadLevel(level);
    player.setPosition(pos);

    //Move camera
    float halfX = mainView.getSize().x / 2.f;
    float halfY = mainView.getSize().y / 2.f;

    if (pos.x < halfX)
        pos.x = halfX;
    else
        pos.x = tileMap.mapPixelSize.x - halfX;

    if (pos.y < halfY)
        pos.y = halfY;
    else
        pos.y = tileMap.mapPixelSize.y - halfY;

    mainView.setCenter(pos);
}

void Scene::reset()
{
    player.reset();
    hud = HUD(font);
    changeLevel(0);
    sf::Vector2f center = player.getPosition();
    center.x += 20.f;
    center.y -= 20.f;
    mainView.setCenter(center);
    parentWindow.setView(mainView);
}
