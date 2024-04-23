#include "AnimationsHandler.hpp"


//constructor
AnimationsHandler::AnimationsHandler(const int setFrames, const int setFPS) 
{
	animationFrames = setFrames;
	frameRate = setFPS;
	animations = std::vector<AnimatedGraphic*>();
	timePassed = 0.0;
}

//adds a new animation to the animations vector
void AnimationsHandler::add(AnimatedGraphic* newAnimation) 
{
	animations.push_back(newAnimation);
}


//calls newFrame in every animation
void AnimationsHandler::updateFrames(const float deltaTime)
{
	timePassed += deltaTime;
	if (timePassed >= 1.0 / frameRate) {
		timePassed = 0;
		for (int i = 0; i < animations.size(); i++) {
			if (animations[i]->isOn()) animations[i]->newFrame(animationFrames);
		}
	} 
}


void AnimationsHandler::draw(sf::RenderWindow& window){
	for (int i = 0; i < animations.size(); i++) {
		if (animations[i]->isOn()) animations[i]->draw(window);
	}
}