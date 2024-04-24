#pragma once
#include "pa9.hpp"
#include "Track.hpp"
#include "GraphicsLayer.hpp"
#include "AnimatedGraphic.hpp"
#include "Road.hpp"
#include "RoadTransition.hpp"
#include "SpeedLines.hpp"
#include "AnimationsHandler.hpp"
#include "Car.h"
#include "CarTypes.h"
#include "functions.hpp"

class GameInitializer {
private:
	//data members
	sf::RenderWindow* window;
	float xRes, yRes;
	sf::Color roadColor, horizonColor, backgroundColor;
public:
	//constructor
	GameInitializer(sf::RenderWindow& win, float xResInit, float yResInit, 
		sf::Color& roadColorInit, sf::Color& horizonColorInit, sf::Color& backgroundColorInit);


	//road initializers
	Road makeStraight() const;
	Road makeLeft() const;
	Road makeRight() const;
	Road makeSharpLeft() const;
	Road makeSharpRight() const;


	//road transition initializers
	RoadTransition makeStraightToLeft() const;
	RoadTransition makeStraightToRight() const;
	RoadTransition makeLeftToStraight() const;
	RoadTransition makeRightToStraight() const;
	RoadTransition makeLeftToSharp() const;
	RoadTransition makeRightToSharp() const;
	RoadTransition makeSharpToLeft() const;
	RoadTransition makeSharpToRight() const;

	//speedlines graphica initializer
	SpeedLines makeSpeed1Lines() const;
	SpeedLines makeSpeed2Lines() const;
	SpeedLines makeSpeed3Lines() const;


	//horizon initializer
	GraphicsLayer makeHorizon() const;	

	//background initializer
	GraphicsLayer makeBackground() const;



	//car initializers
	Car* makeSportsCar() const;
	Car* makeSafetyCar() const;
	Car* makeCopCar() const;


	//handles track1-specific setup
	Track loadTrack1(std::string& musicFilePath) const;

	//handles track2-specific setup
	Track loadTrack2(std::string& musicFilePath) const;
};