#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.hpp"

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    const Animation *animation = NULL;
    bool isPaused;
    int currentFrame;
    const sf::Texture *texture;
    sf::Time currentTime;
    sf::Vertex vertices[4];

public:
    AnimatedSprite(sf::Time frameTime = sf::seconds(0.2f),
                   bool paused = false, bool looped = true);

    void update(sf::Time deltaTime);
    void setAnimation(const Animation &animation);
    void play();
    void play(const Animation &animation);
    void pause();
    void stop();
    void setColor(const sf::Color &color);
    const Animation *getAnimation() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    bool isPlaying() const;
    void setFrame(int newFrame, bool resetTime = true);

    sf::Time frameTime;
    bool isLooped;
};

#endif