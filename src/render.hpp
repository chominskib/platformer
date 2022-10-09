#ifndef RENDER_HPP
#define RENDER_HPP

#include <SFML/Graphics.hpp>
#include "hitbox.hpp"
#include "entity.hpp"
#include <string>

class Entity;

class Renderer{
	sf::Font font;
	sf::RenderWindow* w;

    public:
	Renderer(sf::RenderWindow*);
	void draw(Entity*);
	void setFrame(double lb, double rb, double db, double ub);
	void drawText(std::string content, int size, Point pos, sf::Color color);
};

class AssetsMgr{
	std::map< std::string, sf::Texture > textures;
    public:
	AssetsMgr();
	sf::Texture& getTexture(std::string s, bool repeated = false);
};

#endif
