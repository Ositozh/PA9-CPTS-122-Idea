#pragma once
#include "pa9.hpp"
#include "GraphicsLayer.hpp"

class AnimatedGraphic : public GraphicsLayer {
protected:
	int frame; //keeps track of the current frame of the animation
	bool active; //shows whether or not the animation is active
public:
	//constructor
	AnimatedGraphic();


	//returns current frame
	int getFrame() const;

	//returns whether animation is active or not 
	bool isOn() const;


	//changes frame to given number
	void setFrame(const int newFrame);

	//toggles the animation on/off by changing active
	void toggle();

	//changes active to either on or off
	void setOn();
	void setOff();


	//updates lines to a new frame
	virtual void newFrame(const int frames)
		= 0;
};