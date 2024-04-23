#pragma once
#include "pa9.hpp"

class Track {
private:
	RoadState currentState; //keeps track of which state in vectors is currently active
	std::vector<int> distances; //holds trigger distances that cause state updates
	std::vector<RoadState> roadStates; //holds different road states for associated distances
public:
	//compiler constructor and destructor work here


	//returns current state
	RoadState getCurrentState() const;

	//returns distances vector
	std::vector<int>& getDistances();

	//returns roadStates vector
	std::vector<RoadState>& getRoadStates();


	//current state setter
	void setCurrentState(RoadState newState);

	//adds new distance and associated roadState to arrays
	void addRoadUpdate(int newDistance, RoadState newState);
};