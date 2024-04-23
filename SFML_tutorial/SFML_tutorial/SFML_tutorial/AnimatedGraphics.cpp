#include "AnimatedGraphic.hpp"

//constructor
AnimatedGraphic::AnimatedGraphic() {
	frame = 0;
	active = false;
}




//returns current frame
int AnimatedGraphic::getFrame() const{
	return frame;
}

bool AnimatedGraphic::isOn() const {
	return active;
}


//changes frame to given number
void AnimatedGraphic::setFrame(const int newFrame) {
	frame = newFrame;
}


//toggles the animation on/off by changing isOn
void AnimatedGraphic::toggle() {
	active = !active;
	frame = 0; //resets to beginning of animation
}

//changes active to either on or off
void AnimatedGraphic::setOn() {
	active = true;
}
void AnimatedGraphic::setOff() {
	active = false;
	frame = 0; //resets to beginning of animation
}