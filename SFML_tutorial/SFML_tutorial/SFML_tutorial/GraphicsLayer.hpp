#pragma once
#include "pa9.hpp"

class GraphicsLayer {
protected:
	sf::VertexArray lines;
public:

	//constructor
	GraphicsLayer();
	//compiler destructor works here


	//returns lines array (not a reference)
	sf::VertexArray getLines() const;

	//returns the current color of the lines
	sf::Color getColor() const;

	
	//adds a line to the vertex array as two vertices
	void addLine(const sf::Vector2f& start, const sf::Vector2f& end);
	void addLine(const unsigned int x1, const unsigned int y1,
		const unsigned int x2, const unsigned int y2);

	//uses bezier curve to create curve with lines
	void addCurve(sf::Vector2f& p0, sf::Vector2f& p1, sf::Vector2f& p2);

	//clears lines
	void clearLines();


	//changes color of all lines to given color
	void setColor(const sf::Color col);
	void setColor(const unsigned int red, const unsigned int green,
		const unsigned int blue);


	//draws all lines in the graphics layer to the given window
	void draw(sf::RenderWindow& window) const;


};