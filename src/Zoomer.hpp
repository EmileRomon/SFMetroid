#ifndef ZOOMER_HPP
#define ZOOMER_HPP

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Scene;

class Zoomer : public sf::Drawable, public sf::Transformable
{

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    AnimatedSprite bodySprite;
    Animation animationBody;

    sf::FloatRect collisionBounds;
    const sf::Vector2f speed;
    float leftLimit;
    float rightLimit;

public:
    Zoomer(const sf::Texture &texture, const sf::Vector2f &position, const float limitRange);
    ~Zoomer(){};

    void update(const sf::Time &deltaTime);

    const sf::Vector2f &getPosition() const;

    void move(const sf::Vector2f &offset);

    sf::FloatRect getGlobalBounds();

    sf::Vector2f movement;
};

#endif
