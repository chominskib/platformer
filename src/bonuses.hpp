#ifndef BONUSES_HPP
#define BONUSES_HPP
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include "events.hpp"

class Bonus : public MovableEntity{
    public:
	Bonus(Point);

	virtual void onCollisionWith(LivingEntity*){};
};

class RedSpeed : public Bonus{
	double speed_mult;
    public:
	RedSpeed(Point);

	void onCollisionWith(LivingEntity*);
};

class BlueJump : public Bonus{
	double height_mult;
    public:
	BlueJump(Point);

	void onCollisionWith(LivingEntity*);
};

class Heart : public Bonus{
	double hp_boost;
    public:
	Heart(Point);

	void onCollisionWith(LivingEntity*);
};

class EndOfLevel : public Bonus{
    public:
	EndOfLevel(Point);

	void onCollisionWith(LivingEntity*);
};

#endif
