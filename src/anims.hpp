#ifndef ANIMS_HPP
#define ANIMS_HPP

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Animation{
	sf::Time step;
	sf::Clock clock;
	std::vector< std::string > texture_names;
    public:
	Animation(std::string);
	Animation(float, std::vector< std::string >);
	std::string getTextureName();
	void reset();
};

class AnimationHandler{
	bool repeated;
	int state;
	std::vector< Animation > anims;
    public:
	AnimationHandler();
	AnimationHandler(std::string s); //for static image
	AnimationHandler(std::vector< Animation > anims, int first_state = 0);
	void set(int state);
	std::string getTextureName();
};


#endif
