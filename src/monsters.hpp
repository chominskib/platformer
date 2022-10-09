#ifndef MONSTERS_HPP
#define MONSTERS_HPP

#include "hitbox.hpp"
#include "events.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Monster : public LivingEntity{
    protected:
	double damage;
    public:
	Monster(Point);
	virtual void AI(Point playerpos, double dt){};
};

class BadBall : public Monster{
    protected:
    public:
	BadBall(Point);
	void onCollisionWith(LivingEntity*);
	void AI(Point playerpos, double dt);
};

#endif
