#include "entity.hpp"

Entity::Entity(Point pos = Point(0, 0)) : hbx(Hitbox(pos.x, pos.x, pos.y, pos.y)), pos(pos), spr(new sf::Sprite){}

void Entity::setTexture(std::string s){
	spr->setTexture(global_assetsmgr.getTexture(s, repeated_texture));
}

void Entity::computeAnimation(){
	setTexture(animations.getTextureName());
}

Point Entity::getPos(){
	return pos;
}

sf::Sprite* Entity::getSprite(){
	return spr;
}

Hitbox Entity::getHitbox(){
	return hbx + pos;
}

MovableEntity::MovableEntity(Point pos = Point(0, 0)) : Entity(pos), v(Point(0, 0)), standing(0), ceiling(0), colliding(0), max_speed(100), max_x_accell(3700){}

Point MovableEntity::getV(){
	return v;
}

LivingEntity::LivingEntity(Point pos = Point(0, 0)) : MovableEntity(pos){}

Player::Player(Point pos = Point(0, 0)) : LivingEntity(pos){
	std::cerr << "Created player" << std::endl;

        animations = AnimationHandler({Animation("player.png"), Animation(0.1f, std::vector<std::string>({"player_left1.png", "player_left2.png"})), Animation(0.1f, std::vector<std::string>({"player_right1.png", "player_right2.png"})), Animation("player_left1.png"), Animation("player_right1.png")});

	max_x_accell = 4000.f, terminal_speed = 1000.f, hp = 100.f, jump_height = 300.f, max_speed = 200;
	
	hbx = Hitbox(-16, 16, -16, 16);
	spr->setOrigin(16.f, 16.f);

	setTexture("player.png");
}

void Player::handleEvent(Event* e){
	std::cerr << "player:\tEvent received by player" << std::endl;
	if(e->type == Event::MoveLeft) v.x -= max_x_accell * e->getTime() * (standing ? 1.0f : air_manouverability);
	if(e->type == Event::MoveRight)v.x += max_x_accell * e->getTime() * (standing ? 1.0f : air_manouverability);
	if(e->type == Event::MoveUp && standing){
		v.y += jump_height;
		pos.y += 0.001f;
	}
	if(e->type == Event::SpeedChange){
		max_x_accell *= e->getV();
		max_speed *= e->getV();
	}
	if(e->type == Event::JumpHeightChange){
		jump_height *= e->getV();
	}
}

void Player::computeAnimation(){
	if(v.x > 0 && standing) animations.set(2);
	if(v.x > 0 && !standing) animations.set(4);
	if(v.x == 0) animations.set(0);
	if(v.x < 0 && standing) animations.set(1);
	if(v.x < 0 && !standing) animations.set(3);

	setTexture(animations.getTextureName());
}

void MovableEntity::move(double dt, double max_height_of_obstacle, bool st, bool ceil){
	std::cerr << "entt:\tEntity " << this << " moves by " << dt << " amount of time with mho " << max_height_of_obstacle << ", " << (st ? "" : "not ") << "standing" << std::endl;
	
	standing = st;
	ceiling = ceil;

	double const_resistance = (standing ? platform_friction_coefficient : 0);
	double vx_sign = (v.x >= 0 ? 1.0f : -1.0f);
	double vx_abs = (v.x >= 0 ? v.x : -v.x);

	double abs_of_new_vx = vx_abs - const_resistance * dt - vx_abs*vx_abs*drag_coefficient * dt;
	if(abs_of_new_vx < 0) abs_of_new_vx = 0;
	if(abs_of_new_vx > max_speed) abs_of_new_vx = max_speed;

	v.x = vx_sign * abs_of_new_vx;

	v.y -= dt * g;
	v.y = std::min(v.y, terminal_speed);

	bool energy_loss = false;

	if(ceiling){
		v.y = std::min(v.y, -0.5f*v.y);
	}else if(max_height_of_obstacle >= 10.0f){
		if(!colliding){
			v.x = -v.x;
			energy_loss = true;
		}
		colliding = true;
	}else if(max_height_of_obstacle > 0.1f){
		pos.y += max_height_of_obstacle;
		v.y = 0;
		colliding = false;
	}else{
		colliding = false;
	}

	if(standing) v.y = std::max(v.y, double(0));
	if(ceiling) v.y = std::min(v.y, double(0));

	pos.x += v.x * dt;
	pos.y += v.y * dt;

	if(energy_loss) v.x /= 2.0f;

	std::cerr << "entt:\tEntity " << this << " pos: " << pos.x << " " << pos.y << std::endl;
	std::cerr << "entt:\tEntity " << this << " vec: " << v.x << " " << v.y << std::endl;
	std::cerr << "entt:\tEntity " << this << " energy: " << v.x*v.x + v.y*v.y << std::endl;
}
