#pragma once
#include "pa9.hpp"
#include "GraphicsLayer.hpp"

class AnimatedGraphic : public GraphicsLayer {
public:
	//compiler constructor and destructor work here


	//changes lines for a new frame of the animation
	virtual void newFrame() = 0; //is different for different animation types
};