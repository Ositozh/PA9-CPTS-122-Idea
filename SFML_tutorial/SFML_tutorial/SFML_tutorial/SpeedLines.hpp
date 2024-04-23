#pragma once
#include "pa9.hpp"
#include "AnimatedGraphic.hpp"

class SpeedLines : public AnimatedGraphic{
private:
	sf::RenderWindow* win; //needed for drawFrame
	//draws a portion of the lines for the animation frame
	void drawFrame(sf::RenderWindow& window, const int start, const int count);
public:
	SpeedLines(sf::RenderWindow& window);
	//compiler destructor works here
	

	//changes lines for a new frame of the animation
	void newFrame(const int frames);
};