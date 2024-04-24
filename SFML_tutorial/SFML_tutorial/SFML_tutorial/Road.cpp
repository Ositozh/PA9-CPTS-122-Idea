#include "Road.hpp"

//Finds and returns the horizontal position of a given coordinate relative to the border
bool Road::carOnRoad(const int xCoord, const int yRes) const 
{
    int farLeft = 99999, farRight = 0;
    for (int i = 0; i < lines.getVertexCount(); i++) {
        if (lines[i].position.x < farLeft && lines[i].position.y < yRes * 0.8) 
            farLeft = lines[i].position.x;
        if (lines[i].position.x > farRight && lines[i].position.y < yRes * 0.8) 
            farRight = lines[i].position.x;
    }

    if (xCoord > farLeft && xCoord < farRight - (.4 * yRes )) return true;
    else return false;
}