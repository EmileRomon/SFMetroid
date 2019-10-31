#include "HUD.hpp"
#include <iostream>
#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

HUD::HUD(sf::Font &font) : fpsDisplay("fps", font), fpsAverage(0.f), currentTime(sf::Time::Zero)
{
    fpsDisplay.setCharacterSize(12);
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(fpsDisplay);
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

void HUD::setPosition(float x, float y)
{
    sf::FloatRect bounds = fpsDisplay.getLocalBounds();
    fpsDisplay.setPosition(x - bounds.width, y);
}
