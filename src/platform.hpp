#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "entity.hpp"
#include "hitbox.hpp"
#include "events.hpp"

class Platform : public Entity{
    protected:
	sf::Color c;
	double width, height;
    public:
	Platform(Point pos, double w, double h, sf::Color = sf::Color(255, 0, 255));
	Platform(double x1, double x2, double y1, double y2, sf::Color = sf::Color(255, 0, 255));
	Platform(int x1, int x2, int y1, int y2, sf::Color = sf::Color(255, 0, 255));
};

#endif
