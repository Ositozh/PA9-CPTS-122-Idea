#pragma once
#include "pa9.hpp"
#include "GraphicsLayer.hpp"

class Road : public GraphicsLayer {
public:
	//compiler constructor and destructor work here


	//checks if car is within bounds and returns true if it is
	bool carOnRoad(const int xCoord, const int yRes) const;
};