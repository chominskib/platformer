#ifndef HITBOX_HPP
#define HITBOX_HPP
#include <vector>

struct Point{
	double x, y;

	Point();
	Point(double, double);
	Point operator+(Point);
	double operator*(Point);
	Point operator*(double);
};

class Hitbox{
	double xL, xR, yD, yU;

    public:
	Hitbox(double, double, double, double);
	
	double operator*(Hitbox);
	bool operator^(Hitbox);
	Hitbox operator+(Point);
};
#endif
