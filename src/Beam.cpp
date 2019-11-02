#include "Beam.hpp"

#include <iostream>

Beam::Beam(const Scene &scene, sf::Vector2f position, sf::Texture &texture, bool goingRight) : parentScene(scene),
                                                                                               sprite(sf::seconds(0.05f), false, true),
                                                                                               collisionBounds(0.f, 0.f, 16.0f, 8.0f),
                                                                                               goingRight(goingRight),
                                                                                               traveled(0.f),
                                                                                               movement(200.f, 0.f)
{
    sprite.setPosition(position);

    animation.setSpriteSheet(texture);
    if (goingRight)
    {
        animation.addFrame(sf::IntRect(685, 1456, 16, 8));
    }
    else
    {
        movement.x = -movement.x;
        animation.addFrame(sf::IntRect(300, 1456, 16, 8));
    }
    sprite.setAnimation(animation);
    sprite.setColor(beamColor);
}

void Beam::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}

void Beam::update(const sf::Time &deltaTime)
{
}

sf::FloatRect Beam::getGlobalBounds()
{
    sf::Vector2f pos = sprite.getPosition();
    collisionBounds.top = pos.y;
    collisionBounds.left = pos.x;
    return collisionBounds;
}

const sf::Vector2f &Beam::getPosition() const
{
    return sprite.getPosition();
}

bool Beam::move(const sf::Vector2f &offset)
{
    traveled += abs(offset.x);
    if (traveled > BEAM_RANGE)
        return false;
    sprite.move(offset);
    return true;
}