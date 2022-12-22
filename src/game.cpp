#include <SFML/Graphics.hpp>
#include "game.hpp"

Game::Game(int w, int h) : w(w), h(h), inputhandler(), player(new Player(Point(100, 100))), renderer(&window){
	global_bookkeeper.setPlayer(player);
	window.create(sf::VideoMode(w, h), "Platformer");
	renderer.setFrame(0, 640, 0, 480);
}

void Game::loadLevel(){
	living_entities.insert(player);
	movable_entities.insert(player);

	RedSpeed* r = new RedSpeed(Point(70, 70));
	movable_entities.insert(r);
	bonuses.insert(r);

	BlueJump* b = new BlueJump(Point(500, 120));
	movable_entities.insert(b);
	bonuses.insert(b);

	Heart* h = new Heart(Point(300, 200));
	movable_entities.insert(h);
	bonuses.insert(h);

	BadBall* bb = new BadBall(Point(500, 200));
	movable_entities.insert(bb);
	monsters.insert(bb);

	EndOfLevel* e = new EndOfLevel(Point(1240, 100));
	movable_entities.insert(e);
	bonuses.insert(e);

	entities.insert(new Platform(0, 10000, 0, 32));
	entities.insert(new Platform(0, 32, 0, 480));
	entities.insert(new Platform(608, 640, 100, 480));
	entities.insert(new Platform(300, 450, 80, 112));

	physics_clock.restart();
}

void Game::run(){
	while(global_bookkeeper.getStage() != Bookkeeper::ENDED) loop();
	global_bookkeeper.clean();
}

void Game::loop(){
	if(global_bookkeeper.getStage() == Bookkeeper::BEFORE) menuloop();
	if(global_bookkeeper.getStage() == Bookkeeper::LVL1) gameloop();
	if(global_bookkeeper.getStage() == Bookkeeper::FINISHED) endloop();
}

void Game::menuloop(){
	sf::Clock clk;
	clk.restart();

	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
			global_bookkeeper.setStage(Bookkeeper::FINISHED);
		}
		if(event.type == sf::Event::KeyPressed){
			loadLevel();
			global_bookkeeper.setStage(Bookkeeper::LVL1);
		}
	}

	window.clear();
	renderer.drawText("Platformer", 72, Point(320, 400), sf::Color::White);
	renderer.drawText(version, 24, Point(320, 300), sf::Color(128, 128, 128));
	renderer.drawText("by chominskib", 12, Point(320, 250), sf::Color(128, 128, 128));
	window.display();

	//FRAMERATE LIMITER
	while(clk.getElapsedTime().asSeconds() < 1.0f/100.0f) sf:sleep(sf::microseconds(10));

}

void Game::gameloop(){
	sf::Clock clk;
	clk.restart();
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
			global_bookkeeper.setStage(Bookkeeper::FINISHED);
		}
		if(event.type == sf::Event::Resized){
			renderer.setFrame(0, event.size.width, 0, event.size.height);
		}
		inputhandler.update(event);
	}

	global_bookkeeper.relax();
	inputhandler.send();

	double dt = physics_clock.getElapsedTime().asSeconds();
	physics_clock.restart();

	for(auto& e : monsters) e->AI(player->getPos(), dt);

	for(auto& e : movable_entities){
		double max_height_of_obstacle = 0.0f;
		bool standing = false;
		bool ceil = false;
		for(auto& e2 : entities){
			if(e == e2) continue;
			max_height_of_obstacle = std::max(max_height_of_obstacle,
			                                  e->getHitbox() * e2->getHitbox());
			standing |= e->getHitbox() ^ e2->getHitbox();
			ceil |= e2->getHitbox() ^ e->getHitbox();
		}
		e->move(dt, max_height_of_obstacle, standing, ceil);
	}

	std::vector< Bonus* > to_del;
	for(auto& e : bonuses){
		for(auto& e2 : living_entities){
			if(colliding.count(std::make_pair(e, e2))){	
				if(!(e->getHitbox() * e2->getHitbox()))
					colliding.erase(std::make_pair(e, e2));
			}else{
				if(e->getHitbox() * e2->getHitbox()){
					e->onCollisionWith(e2);
					colliding.insert(std::make_pair(e, e2));
					to_del.push_back(e);
				}
			}
		}
	}

	for(auto& e : monsters){
		for(auto& e2 : living_entities){
			if(e->getHitbox() * e2->getHitbox()){
				e->onCollisionWith(e2);
			}
		}
	}

	for(auto e : to_del){
		bonuses.erase(e);
		movable_entities.erase(e);
		delete e;
	}

	renderer.setFrame(int(player->getPos().x)/640*640, int(player->getPos().x)/640*640 + 640, 0, 480);

	window.clear();
	for(auto e : entities) renderer.draw(e);
	for(auto e : movable_entities) renderer.draw(e);
	window.display();

	//FRAMERATE LIMITER
	while(clk.getElapsedTime().asSeconds() < 1.0f/100.0f) sf:sleep(sf::microseconds(10));
}

void Game::endloop(){
	sf::Clock clk;
	clk.restart();
	sf::Event event;
	while(window.pollEvent(event)){
		if(event.type == sf::Event::Closed){
			window.close();
			global_bookkeeper.setStage(Bookkeeper::FINISHED);
		}
		if(event.type == sf::Event::KeyPressed){
			loadLevel();
			global_bookkeeper.setStage(Bookkeeper::LVL1);
		}
	}

	window.clear();
	renderer.setFrame(0, w, 0, h);
	renderer.drawText("See you again!", 72, Point(320, 400), sf::Color::White);
	window.display();

	//hold message for some time
	while(clk.getElapsedTime().asSeconds() < 3.0f) sf:sleep(sf::microseconds(10));
	exit(0);
}
