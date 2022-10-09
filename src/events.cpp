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
		std::cerr << "ihdl:\tAttempting to send LeftDown with " << t.asSeconds() << std::endl;
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveLeft, t));
		std::cerr << "ihdl:\tSent LeftDown!" << std::endl;
	}
	if(isRightDown){
		std::cerr << "ihdl:\tAttempting to send RightDown with " << t.asSeconds() << std::endl;
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveRight, t));
		std::cerr << "ihdl:\tSent RightDown!" << std::endl;
	}
	if(isUpDown){
		std::cerr << "ihdl:\tAttempting to send UpDown with " << t.asSeconds() << std::endl;
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveUp, t));
		std::cerr << "ihdl:\tSent UpDown!" << std::endl;
	}
	if(isDownDown){
		std::cerr << "ihdl:\tAttempting to send DownDown with " << t.asSeconds() << std::endl;
		global_bookkeeper.add(new Event(global_bookkeeper.getPlayer(), Event::MoveDown, t));
		std::cerr << "ihdl:\tSent DownDown!" << std::endl;
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

bool Bookkeeper::cmp::operator()(std::pair< sf::Time, Event* > a, std::pair< sf::Time, Event* > b){
	return a.first > b.first;
}

void Bookkeeper::execute(Event* e){
	if(e->target != nullptr){
		std::cerr << "bkpr:\tExecuting as normal event" << std::endl;
		e->execute();
	}else{
		if(e->type == Event::EOLHit) exit(0);
	}
}

void Bookkeeper::relax(){
	while(!pq.empty() && pq.top().first < clk.getElapsedTime()){
		std::cerr << "bkpr:\tAttempting to execute event " << pq.top().second << std::endl;
		execute(pq.top().second);
		std::cerr << "bkpr:\tExecuted event " << pq.top().second << std::endl;
		delete pq.top().second;
		pq.pop();
	}
}

void Bookkeeper::clean(){
	while(!pq.empty()){
		delete pq.top().second;
		pq.pop();
	}
	std::cerr << "bkpr:\tCleaned queue" << std::endl;
}

void Bookkeeper::add(Event* e, sf::Time t){
	std::cerr << "bkpr:\tAdded event " << e << " with time " << t.asSeconds() << std::endl;
	pq.push(std::make_pair(clk.getElapsedTime() + t, e));
}

void Bookkeeper::setPlayer(Player* p){
	player = p;
}

Entity* Bookkeeper::getPlayer(){
	return player;
}
