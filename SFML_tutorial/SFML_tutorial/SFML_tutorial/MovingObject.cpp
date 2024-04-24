#include "MovingObject.hpp"

//changes lines to move object down the screen
void MovingObject::newFrame(const int frames) {

	//initializes startState only on the first call
	if (firstRun) {
		startState = lines;
		firstRun = false;
	}

	
	if (frame == 0) {
		lines = startState;
	}
	else if (frame <= frames) {
		//move object down the screen
		for (int i = 0; i < lines.getVertexCount(); i++) {
			if (position== -1) lines[i].position.x -= 20;
			else if (position == 1) lines[i].position.x += 20;

			lines[i].position.y += 5.5;
		}

		//scale around adjusted position
		float scaleFactor = .024;
		if (position == 0) scaleFactor = .04 - frame * .00004;
		scale(scaleFactor);

		if (frame == frames) {
			active = false;
			frame = -1;
		}
	}
	frame++;
}
//scales lines
void MovingObject::scale(const float scale) {

	//find center point of lines
	sf::Vector2f center;
	for (int i = 0; i < lines.getVertexCount(); i++) {
		center.x += lines[i].position.x;
		center.y += lines[i].position.y;
	}
	center.x = center.x / lines.getVertexCount();
	center.y = center.y / lines.getVertexCount();

	//increase distance of points in lines from the center of lines
	//by the given scale
	for (int i = 0; i < lines.getVertexCount(); i++) {
		lines[i].position.x += (lines[i].position.x - center.x) * scale;
		if(position == 0) 
			lines[i].position.y += (lines[i].position.y - center.y) * scale * .7;
		else lines[i].position.y += (lines[i].position.y - center.y) * scale;
	}
}


void MovingObject::shiftX(const float xShift) {
	for (int i = 0; i < lines.getVertexCount(); i++) {
		lines[i].position.x += xShift;
	}
}
