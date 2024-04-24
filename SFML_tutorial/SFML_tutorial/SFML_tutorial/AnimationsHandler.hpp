#pragma once
#include "pa9.hpp"
#include "AnimatedGraphic.hpp"

class AnimationsHandler {
private:
	//determines the universal number of frames per animation and how often they update
	int animationFrames, frameRate;

	//keeps track of time since last frame update
	float timePassed;

	//stores all animations in one vector
	std::vector<AnimatedGraphic*> animations;
public:
	//constructor
	AnimationsHandler(const int setFrames = 6, const int setFPS = 10);

	//changes frameRate
	void setFrameRate(const int newFPS);


	//adds a new animation to the animations vector
	void add(AnimatedGraphic* newAnimation);


	//calls newFrame for every animation
	void updateFrames(const float deltaTime);

	//draws every active animation
	void draw(sf::RenderWindow& window);
};