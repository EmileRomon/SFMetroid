#ifndef GAME_HPP
#define GAME_HPP

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
	//const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
};

#endif
