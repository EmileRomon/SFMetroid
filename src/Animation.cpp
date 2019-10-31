#include "Animation.hpp"

Animation::Animation() : texture(NULL),
                         haveStopFrame(false)
{
}

void Animation::addFrame(sf::IntRect rect)
{
    frames.push_back(rect);
}

void Animation::addStopFrame(sf::IntRect rect)
{
    stopFrame = rect;
    haveStopFrame = true;
}

void Animation::setSpriteSheet(const sf::Texture &tex)
{
    texture = &tex;
}

int Animation::getSize() const
{
    return frames.size();
}

const sf::IntRect &Animation::getFrame(int index) const
{
    if (index < 0)
    {
        if (haveStopFrame)
            return stopFrame;
        return frames[0];
    }
    return frames[index];
}