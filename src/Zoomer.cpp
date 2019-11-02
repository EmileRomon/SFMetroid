#include "Zoomer.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

Zoomer::Zoomer(const sf::Texture &texture, const sf::Vector2f &position) : bodySprite(sf::seconds(0.5f)),
                                                                           collisionBounds(0.f, 0.f, 16.f, 16.f),
                                                                           speed(50.f, 0.f)
{
    animationBody.setSpriteSheet(texture);
    animationBody.addFrame(sf::IntRect(186, 10, 23, 16));
    animationBody.addFrame(sf::IntRect(218, 10, 23, 16));
    animationBody.addFrame(sf::IntRect(250, 10, 23, 16));

    bodySprite.setAnimation(animationBody);

    bodySprite.setPosition(position);

    leftLimit = position.x - 50.f;
    rightLimit = position.x + 50;
    movement.x = speed.x;
}

void Zoomer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(bodySprite);
    /*sf::RectangleShape s;
    s = sf::RectangleShape(sf::Vector2f(collisionBounds.width, collisionBounds.height));
    s.setFillColor(sf::Color::Red);
    s.setPosition(collisionBounds.left, collisionBounds.top);
    target.draw(s);*/
}

void Zoomer::update(const sf::Time &deltaTime)
{
    if (getPosition().x > rightLimit)
    {
        movement.x = -speed.x;
    }
    else if (getPosition().x < leftLimit)
    {
        movement.x = speed.x;
    }
    if (animationBody.getSize() != bodySprite.getAnimation()->getSize())
    {
        bodySprite.setAnimation(animationBody);
    }

    bodySprite.update(deltaTime);
}

const sf::Vector2f &Zoomer::getPosition() const
{
    return bodySprite.getPosition();
}

void Zoomer::move(const sf::Vector2f &offset)
{
    bodySprite.move(offset);
}

sf::FloatRect Zoomer::getGlobalBounds()
{
    sf::Vector2f pos = bodySprite.getPosition();
    collisionBounds.top = pos.y;
    collisionBounds.left = pos.x;

    return collisionBounds;
}