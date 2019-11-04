#ifndef GAME_HPP
#define GAME_HPP

#define WORLD_MUSIC_FILE_PATH "./ressources/audio/Brinstar.ogg"
#define FRAME_RATE 1.f / 60.f

class Scene;

class Game
{

private:
	sf::RenderWindow window;
	Scene scene;
	float deltaTime;

	void processEvents();
	void update(const sf::Time &delta);
	void render();
	void frameAverage(const sf::Time &time);

public:
	Game();
	void run();
};

#endif
