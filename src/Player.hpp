#ifndef PLAYER_HPP
#define PLAYER_HPP

#define JUMP_SOUND_FILE_PATH "./ressources/audio/jump.wav"
#define BEAM_SOUND_FILE_PATH "./ressources/audio/beam.wav"
#define LAND_SOUND_FILE_PATH "./ressources/audio/land.wav"
#define HURT_SOUND_FILE_PATH "./ressources/audio/hurt.ogg"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "AnimatedSprite.hpp"
#include "Animation.hpp"

class Scene;

class Player : public sf::Drawable, public sf::Transformable
{

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    void startJump();

    void checkFire();

    Scene &parentScene;

    AnimatedSprite sprite;
    Animation animationRunLeft;
    Animation animationRunRight;
    Animation animationJumpLeft;
    Animation animationJumpRight;

    sf::Sound jumpSound;
    sf::SoundBuffer jumpSoundBuff;
    sf::Sound beamSound;
    sf::SoundBuffer beamSoundBuff;
    sf::Sound landSound;
    sf::SoundBuffer landSoundBuff;
    sf::Sound hurtSound;
    sf::SoundBuffer hurtSoundBuff;

    bool facingRight;

    float jumpProgress;
    sf::FloatRect collisionBounds;

    bool canFire;
    sf::Time fireCountdown;
    const sf::Time fireRate;
    sf::Time invincibilityCountdown;
    const sf::Time invincibilityTime;
    const sf::Time knockbackDelay;

public:
    Player(Scene &scene, const sf::Texture &texture, const sf::Vector2f &position);
    ~Player(){};

    void update(const sf::Time &deltaTime);

    const sf::Vector2f &getPosition() const;

    void move(const sf::Vector2f &offset);
    void landing(const sf::Vector2f &offset);

    sf::FloatRect getGlobalBounds();

    void setPosition(sf::Vector2f &position);

    void dealDamage(int damageTaken);

    void reset();

    //Keys flags
    bool leftPressed;
    bool rightPressed;
    bool downPressed;
    bool jumpPressed;
    bool firePressed;

    bool isJumping;
    bool canJump;

    bool isDamaged;
    bool isDead;

    int health;

    sf::Vector2f movement;

    const float gravity = 200.f;
    const float jumpHeight = 390.f;
};

#endif
