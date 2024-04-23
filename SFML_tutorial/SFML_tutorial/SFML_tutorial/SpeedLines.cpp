#include "SpeedLines.hpp"

SpeedLines::SpeedLines(sf::RenderWindow& window) {
	win = &window;
	std::cout << "in";
}


//draws a portion of the lines for the animation frame
void SpeedLines::drawFrame(sf::RenderWindow& window, const int start, const int count) {
	if (start + count <= lines.getVertexCount()) {
		window.draw(&lines[start], count, sf::Lines);
	}
}

//changes lines for a new frame of the animation
void SpeedLines::newFrame(const int frames)
{
	if (frame == frames * 2) frame = 0;

	int drawableVertices = 100 / frames;
	int startVertex = frame * drawableVertices;
	drawFrame(*win, startVertex, drawableVertices);
	frame++;
} 