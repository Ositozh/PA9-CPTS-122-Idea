#include "GraphicsLayer.hpp"

//constructor
GraphicsLayer::GraphicsLayer() 
{
	lines.setPrimitiveType(sf::Lines); //all non-car graphics done with lines
}




//returns lines array
const sf::VertexArray& GraphicsLayer::getLines() const
{
    return lines;
}




//adds a line to the vertex array as two vertices
void GraphicsLayer::addLine(const sf::Vector2f& start, const sf::Vector2f& end) 
{
    lines.append(sf::Vertex(start));
    lines.append(sf::Vertex(end));
}
void GraphicsLayer::addLine(const unsigned int x1, const unsigned int y1,
    const unsigned int x2, const unsigned int y2) 
{
    sf::Vector2f start(x1, y1), end(x2, y2);
    addLine(start, end);
}


//uses bezier curve to create curve with lines
void GraphicsLayer::addCurve(sf::Vector2f& p0, sf::Vector2f& p1, sf::Vector2f& p2)
{
    sf::Vector2f endPoint = p0;
    for (float t = 0; t < 1; t += 0.04) {
        sf::Vector2f startPoint = endPoint;
        endPoint = (1 - t) * (1 - t) * p0 + 2 * (1 - t) * t * p1 + t * t * p2;
        lines.append(startPoint);
        lines.append(endPoint);
    }
}




//changes the color of all lines for the graphics layer
void GraphicsLayer::setColor(const sf::Color col) {
    for (int i = 0; i < lines.getVertexCount(); i++) {
        lines[i].color = col;
    }
}
void GraphicsLayer::setColor(const unsigned int red, const unsigned int green,
    const unsigned int blue) 
{
    sf::Color col(red, green, blue);
    setColor(col);
}




//draws all lines in the graphics layer to the given window
void GraphicsLayer::draw(sf::RenderWindow& window) const
{
    window.draw(lines);
}