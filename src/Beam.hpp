#ifndef BEAM_HPP
#define BEAM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Scene;

class Beam : public sf::Drawable, public sf::Transformable
{

#define BEAM_RANGE 75

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    const Scene &parentScene;
    AnimatedSprite sprite;
    Animation animation;
    sf::FloatRect collisionBounds;
    bool goingRight;
    float traveled;
    const sf::Color beamColor = sf::Color(248, 160, 8);

public:
    Beam(const Scene &scene, sf::Vector2f position, sf::Texture &texture, bool goingRight);
    ~Beam(){};

    void update(const sf::Time &deltaTime);

    const sf::Vector2f &getPosition() const;

    bool move(const sf::Vector2f &offset);

    sf::FloatRect getGlobalBounds();

    sf::Vector2f movement;
};

#endif
