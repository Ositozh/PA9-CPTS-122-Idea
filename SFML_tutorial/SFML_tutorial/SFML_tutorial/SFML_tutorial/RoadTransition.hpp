#pragma once
#include "AnimatedGraphic.hpp"

class RoadTransition : public AnimatedGraphic {
private:
	sf::VertexArray lines;
public:


	//changes lines for a new frame of the animation
	void newFrame();
};