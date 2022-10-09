#include "anims.hpp"

Animation::Animation(std::string texture_name) : step(sf::seconds(1)), texture_names({texture_name}){
	clock.restart();
}

Animation::Animation(float t, std::vector< std::string > texture_names) : step(sf::seconds(t)), texture_names(texture_names){
	clock.restart();
}

std::string Animation::getTextureName(){
	return texture_names[int(clock.getElapsedTime().asSeconds()/step.asSeconds())%(texture_names.size())];
}

void Animation::reset(){
	clock.restart();
}

AnimationHandler::AnimationHandler(std::string s) : anims({Animation(1.0f, {s})}), state(0){}

AnimationHandler::AnimationHandler() : AnimationHandler("error.png"){}

AnimationHandler::AnimationHandler(std::vector< Animation > anims, int first_state) : anims(anims), state(first_state){}

void AnimationHandler::set(int new_state){
	if(state == new_state) return;
	state = new_state;
	anims[state].reset();
}

std::string AnimationHandler::getTextureName(){
	return anims[state].getTextureName();
}

