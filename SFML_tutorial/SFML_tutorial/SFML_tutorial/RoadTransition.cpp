#include "RoadTransition.hpp"


//adds 3 vectors to roadInitState, must be called 4x total
void RoadTransition::addStateVectors(const float x1, const float y1, const float x2,
	const float y2, const float x3, const float y3)
{
	roadInitState.push_back(sf::Vector2f(x1, y1));
	roadInitState.push_back(sf::Vector2f(x2, y2));
	roadInitState.push_back(sf::Vector2f(x3, y3));
}


//changes lines for a new frame of the animation
void RoadTransition::newFrame(const int frames)
{

	if (roadInitState.size() < 12) {
		throw std::exception("Road Transition Not Fully Initialized");
	}

	GraphicsLayer* temp = new GraphicsLayer;
	if (frame == 0) {
		//sets lines to the start state of the animation
		temp->addCurve(roadInitState[0], roadInitState[1], roadInitState[2]);
		temp->addCurve(roadInitState[3], roadInitState[4], roadInitState[5]);
		lines = temp->getLines();

		roadCurrState.clear();
		//updates current state
		for (int i = 0; i < 6; i++) {
			roadCurrState.push_back(roadInitState[i]);
		}
	}
	else if (frame < frames) {
		temp->clearLines();
		float p1x, p2x, p3x, p1y, p2y, p3y;
		sf::Vector2f p1, p2, p3;

		p1x = roadCurrState[0].x + (roadInitState[6].x - roadCurrState[0].x) / (frames - frame);
		p1y = roadCurrState[0].y + (roadInitState[6].y - roadCurrState[0].y) / (frames - frame);
		p2x = roadCurrState[1].x + (roadInitState[7].x - roadCurrState[1].x) / (frames - frame);
		p2y = roadCurrState[1].y + (roadInitState[7].y - roadCurrState[1].y) / (frames - frame);
		p3x = roadCurrState[2].x + (roadInitState[8].x - roadCurrState[2].x) / (frames - frame);
		p3y = roadCurrState[2].y + (roadInitState[8].y - roadCurrState[2].y) / (frames - frame);

		p1 = sf::Vector2f(p1x, p1y);
		p2 = sf::Vector2f(p2x, p2y);
		p3 = sf::Vector2f(p3x, p3y);

		temp->addCurve(p1, p2, p3);
		
		roadCurrState[0] = p1;
		roadCurrState[1] = p2;
		roadCurrState[2] = p3;


		p1x = roadCurrState[3].x + (roadInitState[9].x - roadCurrState[3].x) / (frames - frame);
		p1y = roadCurrState[3].y + (roadInitState[9].y - roadCurrState[3].y) / (frames - frame);
		p2x = roadCurrState[4].x + (roadInitState[10].x - roadCurrState[4].x) / (frames - frame);
		p2y = roadCurrState[4].y + (roadInitState[10].y - roadCurrState[4].y) / (frames - frame);
		p3x = roadCurrState[5].x + (roadInitState[11].x - roadCurrState[5].x) / (frames - frame);
		p3y = roadCurrState[5].y + (roadInitState[11].y - roadCurrState[5].y) / (frames - frame);

		p1 = sf::Vector2f(p1x, p1y);
		p2 = sf::Vector2f(p2x, p2y);
		p3 = sf::Vector2f(p3x, p3y);

		temp->addCurve(p1, p2, p3);

		roadCurrState[3] = p1;
		roadCurrState[4] = p2;
		roadCurrState[5] = p3;

		lines = temp->getLines();
	}
	else {
		temp->clearLines();
		//sets lines to the end state of the animation
		temp->addCurve(roadInitState[6], roadInitState[7], roadInitState[8]);
		temp->addCurve(roadInitState[9], roadInitState[10], roadInitState[11]);
		lines = temp->getLines();

		frame = -1; //gets set to 0 by following increment
	}
	frame++;
	delete temp;
} 