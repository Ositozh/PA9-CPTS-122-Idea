#pragma once
#include "AnimatedGraphic.hpp"
#include "Road.hpp"

class RoadTransition : public AnimatedGraphic {
private:
	//holds 4 sets of the 3 arguments used for each road line initialization
	//first 6 are start state lines and last 6 are end state lines
	std::vector<sf::Vector2f> roadInitState;

	//holds last state used for lines
	std::vector<sf::Vector2f> roadCurrState;
public:
	//compiler constructor and destructor work here	


	//adds 3 vectors to roadInitState, must be called twice for start and end states
	void addStateVectors(const float x1, const float y1, const float x2, 
		const float y2, const float x3, const float y3);


	//changes lines for a new frame of the animation
	void newFrame(const int frames);
};