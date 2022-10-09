#include "bonuses.hpp"

Bonus::Bonus(Point pos) : MovableEntity(pos){}

RedSpeed::RedSpeed(Point pos) : Bonus(pos){
	hbx = Hitbox(-8, 8, -8, 8);
	spr->setOrigin(8.f, 8.f);
	animations = AnimationHandler("ball.png");
	spr->setColor(sf::Color(255, 0, 0));
}

BlueJump::BlueJump(Point pos) : Bonus(pos){
	hbx = Hitbox(-8, 8, -8, 8);
	spr->setOrigin(8.f, 8.f);
	animations = AnimationHandler("ball.png");
	spr->setColor(sf::Color(0, 0, 255));
}

Heart::Heart(Point pos) : Bonus(pos){
	hbx = Hitbox(-8, 8, -8, 8);
	spr->setOrigin(8.f, 8.f);
	animations = AnimationHandler("heart.png");
}

EndOfLevel::EndOfLevel(Point pos) : Bonus(pos){
	hbx = Hitbox(-16, 16, -16, 16);
	spr->setOrigin(16.f, 16.f);
	animations = AnimationHandler("flag.png");
}

void RedSpeed::onCollisionWith(LivingEntity* le){
	global_bookkeeper.add(new Event(le, Event::SpeedChange, 1.5f));
	global_bookkeeper.add(new Event(le, Event::SpeedChange, 1.0f/1.5f), sf::seconds(10));
}

void BlueJump::onCollisionWith(LivingEntity* le){
	global_bookkeeper.add(new Event(le, Event::JumpHeightChange, 1.5f));
	global_bookkeeper.add(new Event(le, Event::JumpHeightChange, 1.0f/1.5f), sf::seconds(10));
}

void Heart::onCollisionWith(LivingEntity* le){
	global_bookkeeper.add(new Event(le, Event::HPChange, 0.1f));
}

void EndOfLevel::onCollisionWith(LivingEntity* le){
	if(le != global_bookkeeper.getPlayer()) return;
	global_bookkeeper.add(new Event(Event::EOLHit));
}
