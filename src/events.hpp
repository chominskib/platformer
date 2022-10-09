#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <queue>
#include <map>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "env_constants.hpp"

class Entity;
class MovableEntity;
class LivingEntity;
class Player;

struct Event{
	Entity* target;
	Event();
	void execute();

	enum EventType{
		HPChange, 
		SpeedChange,
		JumpHeightChange,
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		EOLHit
	};

	EventType type;

	union{
		double value;
		sf::Time time;
	};

	Event(EventType);
	Event(EventType, double);
	Event(EventType, sf::Time);
	Event(Entity*, EventType);
	Event(Entity*, EventType, double);
	Event(Entity*, EventType, sf::Time);

	double getTime();
	double getV();
};


class Bookkeeper{
	struct cmp{ 
		bool operator()(std::pair< sf::Time, Event* >, std::pair< sf::Time, Event* >);
	};
	sf::Clock clk;
	std::priority_queue< std::pair< sf::Time, Event* >,
	                     std::vector< std::pair< sf::Time, Event* > >,
		             cmp > pq;
	Player* player;
    public:
	Bookkeeper(){}

	void execute(Event*);
	void relax();
	void clean();
	void add(Event*, sf::Time = sf::seconds(0.0f));
	void setPlayer(Player*);
	Entity* getPlayer();
};

class InputHandler{
	sf::Clock clk;
	bool isLeftDown, isRightDown, isUpDown, isDownDown;
    public:
	InputHandler();
	void update(sf::Event);
	void send();
};


#endif
