#include "entity.hpp"
#include "events.hpp"
#include "platform.hpp"
#include "bonuses.hpp"
#include "render.hpp"
#include "monsters.hpp"
#include <vector>
#include <iostream>
#include <set>

class Game{
	sf::RenderWindow window;
	sf::Clock physics_clock;
	sf::Font font;

	Player* player;
	InputHandler inputhandler;
	Renderer renderer;

	std::set< Entity* > entities;
	std::set< MovableEntity* > movable_entities;
	std::set< LivingEntity* > living_entities;
	std::set< Bonus* > bonuses;
	std::set< Monster* > monsters;

	std::set< std::pair< Bonus*, LivingEntity* > > colliding;

	int h, w;

	enum status{
		BEFORE, PLAYING, FINISHED, ENDED
	};

	status stage;
	int level = -1;

	void loadLevel();
		
	void menuloop();
	void gameloop();
	void endloop();

	void loop();

    public:
	Game(int, int);
	void run();
};
