#include "hitbox.hpp"

Point::Point() : x(0), y(0){}

Point::Point(double x, double y) : x(x), y(y){}

Point Point::operator+(Point p){
	return Point(x+p.x, y+p.y);
}

double Point::operator*(Point p){
	return x*p.y - y*p.x;
}

Point Point::operator*(double s){
	return Point(x*s, y*s);
}

Hitbox::Hitbox(double x1, double x2, double y1, double y2) : xL(std::min(x1, x2)), xR(std::max(x1, x2)), yD(std::min(y1, y2)), yU(std::max(y1, y2)){}


double Hitbox::operator*(Hitbox h){
	if(xR <= h.xL || h.xR <= xL || h.yD >= yU) return 0.0f;
	return std::max(double(0), h.yU - yD);
}

bool Hitbox::operator^(Hitbox h){
	if(xR <= h.xL || h.xR <= xL || yU <= h.yU) return false;
	//TODO: change this fixed 5 into "climbability ratio"
	return yD >= h.yU - 5.0f && yD <= h.yU + 0.1f;
}

Hitbox Hitbox::operator+(Point pos){
	return Hitbox(xL+pos.x, xR+pos.x, yD+pos.y, yU+pos.y);
}
