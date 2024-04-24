#pragma once
#include "pa9.hpp"
#include "AnimatedGraphic.hpp"

class MovingObject : public AnimatedGraphic {
private:
	//indicates if startState has been set to initial lines
	bool firstRun = true;

	//holds object start state
	sf::VertexArray startState;

	//makes object bigger as it moves down the screen
	//scale of 1 doubles the size of the object
	void scale(const float scale);
public:
	//changes lines to move object down the screen
	void newFrame(const int frames);

	//shifts the x position of the object
	void shiftX(const float xShift);

	float xRes;

	//used to change x position shifting
	int position; //-1 is left, 0 is middle, 1 is right
};