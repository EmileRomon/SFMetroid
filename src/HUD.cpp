#include <cmath>

#include "HUD.hpp"

HUD::HUD(sf::Font &font) : fpsDisplay("fps", font),
                           fpsAverage(0.f),
                           currentTime(sf::Time::Zero),
                           healthDisplay("99 hp", font)
{
    fpsDisplay.setCharacterSize(12);
    healthDisplay.setCharacterSize(12);
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(fpsDisplay);
    target.draw(healthDisplay);
}

void HUD::update(const sf::Time &frameTime)
{
    currentTime += frameTime;
    if (currentTime > displayRate)
    {
        currentTime = sf::Time::Zero;

        float sec = frameTime.asSeconds();

        if (std::abs(fpsAverage - sec) > TIME_EPSILON)
        {
            fpsAverage = sec;
            fpsDisplay.setString(std::to_string((int)(1.f / fpsAverage)) + " fps");
        }
    }
}

void HUD::sethealth(const int health)
{
    healthDisplay.setString((std::to_string(health))+ " hp");
}

void HUD::setPosition(float x, float y)
{
    sf::FloatRect bounds = fpsDisplay.getLocalBounds();
    fpsDisplay.setPosition(x - bounds.width, y);
    bounds = healthDisplay.getLocalBounds();
    healthDisplay.setPosition(x - bounds.width - 270.f, y);
}
