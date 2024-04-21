#include "Road.hpp"

//Finds and returns the horizontal position of a given coordinate relative to the border
bool Road::carOnRoad(const int xCoord) const 
{
    int farLeft = 99999, farRight = 0;
    for (int i = 0; i < lines.getVertexCount(); i++) {
        if (lines[i].position.x < farLeft) farLeft = lines[i].position.x;
        if (lines[i].position.x > farRight) farRight = lines[i].position.x;
    }

    if (xCoord > farLeft && xCoord < farRight) return true;
    else return false;
}