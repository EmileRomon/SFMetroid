#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#define TIME_EPSILON 0.0001

class HUD : public sf::Drawable, public sf::Transformable
{
private:
    sf::Text fpsDisplay;
    float fpsAverage;
    sf::Time currentTime;
    sf::Time displayRate = sf::seconds(0.1);
    sf::Font font;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    HUD(sf::Font &font);
    HUD(){};
    ~HUD(){};

    void update(const sf::Time &frameTime);
    virtual void setPosition(float x, float y);
};

#endif