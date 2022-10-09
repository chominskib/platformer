#include <SFML/Graphics.hpp>
#include "game.hpp"

int main(){
	std::cerr << "Started app" << std::endl;
	Game game(640, 480);
	game.run();
}
