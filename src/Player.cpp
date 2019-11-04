#include <cassert>

#include "Player.hpp"
#include "Scene.hpp"

Player::Player(Scene &scene, const sf::Texture &texture, const sf::Vector2f &position) : parentScene(scene),
                                                                                         sprite(sf::seconds(0.05f)),
                                                                                         facingRight(true),
                                                                                         collisionBounds(0.f, 0.f, 13.0f, 30.0f),
                                                                                         canFire(true),
                                                                                         fireCountdown(sf::Time::Zero),
                                                                                         fireRate(sf::seconds(0.6f)),
                                                                                         invincibilityCountdown(sf::Time::Zero),
                                                                                         invincibilityTime(sf::seconds(1.5f)),
                                                                                         knockbackDelay(sf::seconds(1.3f)),
                                                                                         leftPressed(false),
                                                                                         rightPressed(false),
                                                                                         downPressed(false),
                                                                                         jumpPressed(false),
                                                                                         firePressed(false),
                                                                                         isJumping(false),
                                                                                         canJump(true),
                                                                                         isDamaged(false),
                                                                                         isDead(false),
                                                                                         health(99)

{
    assert(jumpSoundBuff.loadFromFile(JUMP_SOUND_FILE_PATH));
    assert(beamSoundBuff.loadFromFile(BEAM_SOUND_FILE_PATH));
    assert(landSoundBuff.loadFromFile(LAND_SOUND_FILE_PATH));
    assert(hurtSoundBuff.loadFromFile(HURT_SOUND_FILE_PATH));

    jumpSound = sf::Sound(jumpSoundBuff);
    jumpSound.setLoop(true);
    beamSound = sf::Sound(beamSoundBuff);
    landSound = sf::Sound(landSoundBuff);
    hurtSound = sf::Sound(hurtSoundBuff);

    animationRunLeft.setSpriteSheet(texture);
    animationRunLeft.addFrame(sf::IntRect(464, 300, 38, 40));
    animationRunLeft.addFrame(sf::IntRect(425, 300, 32, 40));
    animationRunLeft.addFrame(sf::IntRect(387, 300, 35, 40));
    animationRunLeft.addFrame(sf::IntRect(349, 300, 36, 40));
    animationRunLeft.addFrame(sf::IntRect(311, 300, 36, 40));
    animationRunLeft.addFrame(sf::IntRect(273, 300, 29, 40));
    animationRunLeft.addFrame(sf::IntRect(237, 300, 31, 40));
    animationRunLeft.addFrame(sf::IntRect(200, 300, 35, 40));
    animationRunLeft.addFrame(sf::IntRect(162, 300, 36, 40));
    animationRunLeft.addFrame(sf::IntRect(124, 300, 35, 40));
    animationRunLeft.addStopFrame(sf::IntRect(352, 135, 27, 40));

    animationRunRight.setSpriteSheet(texture);
    animationRunRight.addFrame(sf::IntRect(503, 300, 41, 40));
    animationRunRight.addFrame(sf::IntRect(541, 300, 35, 40));
    animationRunRight.addFrame(sf::IntRect(579, 300, 35, 40));
    animationRunRight.addFrame(sf::IntRect(616, 300, 36, 40));
    animationRunRight.addFrame(sf::IntRect(654, 300, 36, 40));
    animationRunRight.addFrame(sf::IntRect(693, 300, 35, 40));
    animationRunRight.addFrame(sf::IntRect(729, 300, 35, 40));
    animationRunRight.addFrame(sf::IntRect(766, 300, 34, 40));
    animationRunRight.addFrame(sf::IntRect(803, 300, 36, 40));
    animationRunRight.addFrame(sf::IntRect(842, 300, 35, 40));
    animationRunRight.addStopFrame(sf::IntRect(624, 135, 30, 40));

    animationJumpLeft.setSpriteSheet(texture);
    animationJumpLeft.addFrame(sf::IntRect(479, 1203, 19, 40));
    animationJumpLeft.addFrame(sf::IntRect(445, 1198, 25, 40));
    animationJumpLeft.addFrame(sf::IntRect(410, 1198, 27, 40));
    animationJumpLeft.addFrame(sf::IntRect(377, 1195, 21, 40));
    animationJumpLeft.addFrame(sf::IntRect(350, 1189, 17, 40));
    animationJumpLeft.addFrame(sf::IntRect(313, 1189, 24, 40));
    animationJumpLeft.addFrame(sf::IntRect(275, 1189, 27, 40));
    animationJumpLeft.addFrame(sf::IntRect(244, 1189, 21, 40));
    animationJumpLeft.addStopFrame(sf::IntRect(352, 135, 27, 40));

    animationJumpRight.setSpriteSheet(texture);
    animationJumpRight.addFrame(sf::IntRect(505, 1203, 19, 40));
    animationJumpRight.addFrame(sf::IntRect(533, 1198, 25, 40));
    animationJumpRight.addFrame(sf::IntRect(566, 1198, 27, 40));
    animationJumpRight.addFrame(sf::IntRect(605, 1195, 21, 40));
    animationJumpRight.addFrame(sf::IntRect(635, 1189, 17, 40));
    animationJumpRight.addFrame(sf::IntRect(666, 1189, 24, 40));
    animationJumpRight.addFrame(sf::IntRect(701, 1189, 27, 40));
    animationJumpRight.addFrame(sf::IntRect(738, 1189, 21, 40));
    animationJumpRight.addStopFrame(sf::IntRect(624, 135, 30, 40));

    sprite.setPosition(position);
    sprite.setAnimation(animationRunRight);
    sprite.stop();
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite);
}

void Player::update(const sf::Time &deltaTime)
{
    fireCountdown -= deltaTime;
    invincibilityCountdown -= deltaTime;

    sprite.update(deltaTime);

    if (isDamaged)
    {
        if (invincibilityCountdown <= knockbackDelay)
        {
            isDamaged = false;
            movement.x = -movement.x;
        }
        else
        {
            movement.x = facingRight ? -50.f : 50.f;
            movement.y = -150.f;
            return;
        }
    }

    if (movement.x != 0.f)
        facingRight = movement.x > 0.f;
    movement.x = movement.y = 0.f;
    movement.y = gravity;
    if (jumpPressed)
    {
        if (canJump)
        {
            canJump = false;
            startJump();
            sprite.play((facingRight) ? animationJumpRight : animationJumpLeft);
        }
    }
    else
        canJump = true;
    if (leftPressed)
        movement.x -= 100.f;
    if (rightPressed)
        movement.x += 100.f;

    if (firePressed)
        checkFire();

    if (isJumping)
    {
        if (jumpProgress > 0)
        {
            jumpProgress -= jumpHeight * deltaTime.asSeconds() * 2; //
            movement.y -= jumpHeight;
        }

        if (movement.x > 0)
        {
            sprite.play(animationJumpRight);
        }
        else if (movement.x < 0)
        {
            sprite.play(animationJumpLeft);
        }
    }
    else
    {
        if (movement.x > 0)
        {
            sprite.play(animationRunRight);
        }
        else if (movement.x < 0)
        {
            sprite.play(animationRunLeft);
        }
        else
            sprite.stop();
    }
}

void Player::startJump()
{
    if (!isJumping)
    {
        canFire = false;
        isJumping = true;
        jumpProgress = jumpHeight;
        jumpSound.play();
    }
}

const sf::Vector2f &Player::getPosition() const
{
    return sprite.getPosition();
}

void Player::move(const sf::Vector2f &offset)
{
    sprite.move(offset);
}

sf::FloatRect Player::getGlobalBounds()
{
    sf::Vector2f pos = sprite.getPosition();
    float offset = 5.f;
    collisionBounds.top = pos.y + offset;
    facingRight ? offset = 5.f : offset = 10.f;
    collisionBounds.left = pos.x + offset;
    return collisionBounds;
}

void Player::landing(const sf::Vector2f &movement)
{
    if (movement.y == 0 && isJumping)
    {
        if (jumpProgress <= 0)
        {
            isJumping = false;
            canFire = true;
            jumpSound.stop();
            landSound.play();
        }
        jumpProgress = 0.f;
    }
    else if (movement.y > 0 && !isJumping)
    {
        isJumping = true;
        jumpProgress = 0.f;
        jumpSound.play();
    }
}

void Player::checkFire()
{
    if (fireCountdown <= sf::Time::Zero)
    {
        if (canFire)
        {
            fireCountdown = fireRate;
            sf::Vector2f pos = sprite.getPosition();
            if (facingRight)
                pos.x += 30.f;
            else
                pos.x -= 5.f;

            pos.y += 10.f;
            parentScene.addBeamShot(pos, facingRight);
            beamSound.play();
        }
    }
}

void Player::setPosition(sf::Vector2f &position)
{
    sprite.setPosition(position);
}

void Player::dealDamage(int damageTaken)
{
    if (invincibilityCountdown <= sf::Time::Zero && !isDead)
    {
        hurtSound.play();
        if (damageTaken > health)
        {
            health = 0;
            isDead = true;
            jumpSound.stop();
            return;
        }
        invincibilityCountdown = invincibilityTime;
        isDamaged = true;
        health -= damageTaken;
    }
}

void Player::reset()
{
    facingRight = true;
    canFire = true;
    fireCountdown = sf::Time::Zero;
    invincibilityCountdown = sf::Time::Zero;
    leftPressed = false;
    rightPressed = false;
    downPressed = false;
    jumpPressed = false;
    firePressed = false;
    isJumping = false;
    canJump = true;
    isDamaged = false;
    isDead = false;
    health = 99;
    sprite.stop();
    jumpSound.stop();
}