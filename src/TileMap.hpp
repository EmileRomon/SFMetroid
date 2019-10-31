#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>

#define TILE_SIZE 16

class TileMap : public sf::Drawable, public sf::Transformable
{

private:
    void load();

    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::VertexArray vertices;
    const sf::Texture &tileset;
    unsigned int levelWidth;
    unsigned int levelHeight;
    const int *levelTiles;
    const int *levelTilesCollision;

    static const int level1[];
    static const int levelc1[];
    static const int level2[];
    static const int levelc2[];

public:
    TileMap(sf::Texture &tileset);
    void loadLevel(const int level);
    bool collision(const sf::FloatRect &bounds, sf::Vector2f &movement, int &trigger);
    bool computeCollision(const sf::FloatRect &bounds, sf::Vector2f &movement, int &trigger);

    sf::Vector2i mapPixelSize;
};

#endif