#include "platform.hpp"


Platform::Platform(Point pos, double w, double h, sf::Color c) : Entity(pos), c(c), width(w), height(h){
	hbx = Hitbox(-width/2, width/2, -height/2, height/2);
	spr->setOrigin(width/2, height/2);
	
	animations = AnimationHandler("bricks_cont.png");
	spr->setTextureRect(sf::IntRect(0, 0, width, height));
	repeated_texture = true;
}
	
Platform::Platform(double x1, double x2, double y1, double y2, sf::Color c) : Platform(Point((x1+x2)/2, (y1+y2)/2), abs(x1-x2), abs(y1-y2), c){}

Platform::Platform(int x1, int x2, int y1, int y2, sf::Color c) : Platform(double(x1), double(x2), double(y1), double(y2), c){}
