#include "monsters.hpp"

Monster::Monster(Point p) : LivingEntity(p){}

BadBall::BadBall(Point p) : Monster(p){
	animations = AnimationHandler("monster1.png");
	max_x_accell = 3800;
	hbx = Hitbox(-16, 16, -16, 16);
	spr->setOrigin(16, 16);
}

void BadBall::onCollisionWith(LivingEntity* le){
	//TODO
	//le->handleEvent(Event(Event::HPChange, -10.f));
}

void BadBall::AI(Point playerpos, double dt){
	if(colliding) return;
	v.x += (pos.x - playerpos.x >= 0 ? -1.0f : 1.0f) * max_x_accell * dt * (standing ? 1.0f : air_manouverability);
}
