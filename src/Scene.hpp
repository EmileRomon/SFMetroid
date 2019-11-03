#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <list>

#include "Player.hpp"
#include "TileMap.hpp"
#include "Beam.hpp"
#include "HUD.hpp"
#include "Zoomer.hpp"

#define TILESET_FILE_PATH "./ressources/texture/tileset.png"
#define PLAYER_TEXTURE_FILE_PATH "./ressources/texture/player.png"
#define HUD_FONT "./ressources/Metroid-Fusion.ttf"
#define ENEMIES_TEXTURE_FILE_PATH "./ressources/texture/enemies.png"

class Player;
class TileMap;

class Scene
{

private:
	Player player;
	TileMap tileMap;
	sf::RenderWindow &parentWindow;
	sf::View mainView;
	std::list<Beam> beamList;
	std::list<Zoomer> zList;
	sf::Texture playerTexture;
	sf::Texture mapTexture;
	sf::Texture enemiesTexture;
	HUD hud;
	sf::Font font;
	sf::Text gameOverText;
	sf::Text restartText;

public:
	Scene(sf::RenderWindow &window);
	~Scene(){};

	void handleEvent(const sf::Event &evt);

	void update(const sf::Time &frameTime);

	void draw();

	void addBeamShot(const sf::Vector2f &position, bool facingRight);

	void changeLevel(int level);

	void reset();
};

#endif
