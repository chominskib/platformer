#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "hitbox.hpp"
#include "events.hpp"
#include "render.hpp"
#include "env_constants.hpp"
#include "anims.hpp"
#include <iostream>

class Event;
namespace Events{
	class HPChange;
	class SpeedChange;
	class JumpHeightChange;
	class Move;
	class MoveLeft;
};
class LivingEntity;

class Entity{
    protected:
	Point pos;
	Hitbox hbx;
	sf::Sprite* spr;

    public:
	Entity(Point);
	virtual void handleEvent(Event* e){};
	virtual void onCollisionWith(LivingEntity* le){};

	bool repeated_texture = false;
	AnimationHandler animations;
	virtual void computeAnimation();
	void setTexture(std::string);

	Hitbox getHitbox();
	Point getPos();
	sf::Sprite* getSprite();
};

class MovableEntity : public Entity{
    protected:
	double max_speed;
	double max_x_accell;
	double terminal_speed;
	bool standing, ceiling, colliding;
	Point v;
    public:
	MovableEntity(Point);
	Point getV();
	void move(double dt, double max_height_of_obstacle, bool standing, bool ceiling);
};

class LivingEntity : public MovableEntity{
    protected:
	double hp;
	double jump_height;

    public:
	LivingEntity(Point);
	//void handleEvent(Event* e);
};

class Player : public LivingEntity{
    public:
	Player(Point);
	void handleEvent(Event* e);
	void computeAnimation() override;
};

#endif
