#include "Track.hpp"



//returns current state
RoadState Track::getCurrentState() const{
	return currentState;
}


//changes current state
void Track::setCurrentState(RoadState newState) {
	currentState = newState;
}


//returns distances vector
std::vector<int>& Track::getDistances(){
	return distances;
}


//returns roadStates vector
std::vector<RoadState>& Track::getRoadStates(){
	return roadStates;
}




//adds new distance and associated roadState to arrays
void Track::addRoadUpdate(int newDistance, RoadState newState) {
	distances.push_back(newDistance);
	roadStates.push_back(newState);
}