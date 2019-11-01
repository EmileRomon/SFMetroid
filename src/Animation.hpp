#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Sound.hpp>

class Animation
{

public:
    Animation();

    void addFrame(sf::IntRect rect);

    void addStopFrame(sf::IntRect rect);

    void setSpriteSheet(const sf::Texture &texture);

    int getSize() const;

    const sf::IntRect &getFrame(int index) const;

    const sf::Texture *texture;
    
private:
    std::vector<sf::IntRect> frames;

    sf::IntRect stopFrame;

    bool haveStopFrame;
};

#endif