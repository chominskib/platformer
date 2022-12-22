#include "render.hpp"
#include <iostream>

Renderer::Renderer(sf::RenderWindow* w) : w(w){
	font.loadFromFile("assets/TangoSans.ttf");
}

void Renderer::draw(Entity* e){
	e->computeAnimation();

	sf::Sprite s = *(e->getSprite());

	s.setPosition(e->getPos().x, e->getPos().y);
	s.setScale(1.0f, -1.0f);

	w->draw(s);
}

void Renderer::setFrame(double lb, double rb, double db, double ub){
	w->setView(sf::View(sf::FloatRect(lb, ub, rb-lb, -(ub-db))));
}

void Renderer::drawText(std::string content, int size, Point pos, sf::Color color){
	sf::Text t;
	t.setFont(font);
	t.setString(content);
	t.setCharacterSize(size);
	t.setFillColor(color);
	t.setPosition(pos.x, pos.y);
	t.setOrigin(t.getLocalBounds().width/2, t.getLocalBounds().height/2);

	t.setScale(1.0f, -1.0f);
	w->draw(t);
}

sf::Texture& AssetsMgr::getTexture(std::string s, bool repeated){
	std::string path = "assets/" + s;

	if(!(textures[path].loadFromFile(path))){
		std::cerr << "Loading error!" << std::endl;
	}

	//TODO change this into map of pairs of string and bool

	textures[path].setRepeated(repeated);
	return textures[path];
}

AssetsMgr::AssetsMgr(){}
