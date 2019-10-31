#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Scene;

class Player : public sf::Drawable, public sf::Transformable
{

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void startJump();

    void checkFire(const sf::Time &deltaTime);

    Scene &parentScene;

    AnimatedSprite sprite;
    Animation animationRunLeft;
    Animation animationRunRight;
    Animation animationJumpLeft;
    Animation animationJumpRight;

    bool facingRight;

    float jumpProgress;
    sf::FloatRect collisionBounds;

    bool canFire;
    sf::Time fireCountdown;
    const sf::Time fireRate;

public:
    Player(Scene &scene, const sf::Texture &texture, const sf::Vector2f &position);
    ~Player(){};

    void update(const sf::Time &deltaTime);

    const sf::Vector2f &getPosition() const;

    void move(const sf::Vector2f &offset);
    void landing(const sf::Vector2f &offset);

    sf::FloatRect getGlobalBounds();

    void setPosition(sf::Vector2f &position);

    //Keys flags
    bool leftPressed;
    bool rightPressed;
    bool downPressed;
    bool jumpPressed;
    bool firePressed;

    bool isJumping;
    bool canJump;

    sf::Vector2f movement;

    const float gravity = 200.f;
    const float jumpHeight = 390.f;
};

#endif
