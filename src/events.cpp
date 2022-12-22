#include "events.hpp"
#include <iostream>

InputHandler::InputHandler(){
	clk.restart();
	isLeftDown = false, isUpDown = false, isRightDown = false, isDownDown = false;
}

void InputHandler::update(sf::Event event){
	if(event.type == sf::Event::KeyPressed){
		if(event.key.code == sf::Keyboard::Left)
			isLeftDown = true;
		if(event.key.code == sf::Keyboard::Right)
			isRightDown = true;
		if(event.key.code == sf::Keyboard::Up)
			isUpDown = true;
		if(event.key.code == sf::Keyboard::Down)
			isDownDown = true;
	}
	if(event.type == sf::Event::KeyReleased){
		if(event.key.code == sf::Keyboard::Left)
			isLeftDown = false;
		if(event.key.code == sf::Keyboard::Right)
			isRightDown = false;
		if(event.key.code == sf::Keyboard::Up)
			isUpDown = false;
		if(event.key.code == sf::Keyboard::Down)
			isDownDown = false;
	}
}

void InputHandler::send(){
	sf::Time t = clk.getElapsedTime();
	clk.restart();
	if(isLeftDown){
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveLeft, t));
	}
	if(isRightDown){
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveRight, t));
	}
	if(isUpDown){
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveUp, t));
	}
	if(isDownDown){
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveDown, t));
	}

}

Event::Event(EventType t) : target(nullptr), type(t){}

Event::Event(EventType t, double v): target(nullptr), type(t), value(v){}

Event::Event(EventType t, sf::Time time) : target(nullptr), type(t), time(time){}

Event::Event(Entity* e, EventType t) : target(e), type(t){}

Event::Event(Entity* e, EventType t, double v) : target(e), type(t), value(v){}

Event::Event(Entity* e, EventType t, sf::Time time) : target(e), type(t), time(time){}

void Event::execute(){
	target->handleEvent(this);
}

double Event::getTime(){
	return time.asSeconds();
}

double Event::getV(){
	return value;
}

Bookkeeper::Bookkeeper(){
	stage = BEFORE;
}

bool Bookkeeper::cmp::operator()(std::pair< sf::Time, Event* > a, std::pair< sf::Time, Event* > b){
	return a.first > b.first;
}

void Bookkeeper::execute(Event* e){
	if(e->target != nullptr){
		e->execute();
	}else{
		if(e->type == Event::EOLHit) setStage(Bookkeeper::FINISHED);
	}
}

void Bookkeeper::relax(){
	while(!pq.empty() && pq.top().first < clk.getElapsedTime()){
		execute(pq.top().second);
		delete pq.top().second;
		pq.pop();
	}
}

void Bookkeeper::clean(){
	while(!pq.empty()){
		delete pq.top().second;
		pq.pop();
	}
}

void Bookkeeper::add(Event* e, sf::Time t){
	pq.push(std::make_pair(clk.getElapsedTime() + t, e));
}

void Bookkeeper::setPlayer(Player* p){
	player = p;
}

Bookkeeper::status Bookkeeper::getStage(){
	return stage;
}

void Bookkeeper::setStage(status s){
	stage = s;
}

Entity* Bookkeeper::getPlayer(){
	return player;
}
