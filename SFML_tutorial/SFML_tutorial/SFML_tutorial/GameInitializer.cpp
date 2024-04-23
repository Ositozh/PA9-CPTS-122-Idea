#include "GameInitializer.hpp"

//constructor
GameInitializer::GameInitializer(sf::RenderWindow& win, float xResInit, float yResInit, sf::Color& roadColorInit,
    sf::Color& horizonColorInit, sf::Color& backgroundColorInit) {

    window = &win;
    xRes = xResInit;
    yRes = yResInit;
    roadColor = roadColorInit;
    horizonColor = horizonColorInit;
    backgroundColor = backgroundColorInit;
}




//makes straight road
Road GameInitializer::makeStraight() const{
    Road straight; //for straight sections (must use curve for transition animations)
    sf::Vector2f p0(0, .85 * yRes);
    sf::Vector2f p1(.51 * xRes / 2, (.85 * yRes + .35 * yRes) / 2);
    sf::Vector2f p2(.51 * xRes, .3285 * yRes);
    straight.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(xRes, .85 * yRes);
    p1 = sf::Vector2f((xRes + .49 * xRes) / 2, (.85 * yRes + .35 * yRes) / 2);
    p2 = sf::Vector2f(.49 * xRes, .3285 * yRes);
    straight.addCurve(p0, p1, p2);

    straight.setColor(roadColor);

    return straight;
}

//makes left turn road
Road GameInitializer::makeLeft() const {
    Road left; //for left turns
    sf::Vector2f p0(xRes, .9 * yRes);
    sf::Vector2f p1(.62 * xRes, .32 * yRes);
    sf::Vector2f p2(.24 * xRes, .352 * yRes);
    left.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(0, .8 * yRes);
    p1 = sf::Vector2f(.4 * xRes, .45 * yRes);
    p2 = sf::Vector2f(.24 * xRes, .342 * yRes);
    left.addCurve(p0, p1, p2);

    left.setColor(roadColor);

    return left;
}

//makes right turn road
Road GameInitializer::makeRight() const {
    Road right; //for right turns
    sf::Vector2f p0(0, .95 * yRes); //start point of curve
    sf::Vector2f p1(.38 * xRes, .32 * yRes); //used to shape curve
    sf::Vector2f p2(.76 * xRes, .352 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(xRes, .8 * yRes);
    p1 = sf::Vector2f(.6 * xRes, .45 * yRes);
    p2 = sf::Vector2f(.76 * xRes, .342 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes sharp right turn road
Road GameInitializer::makeSharpRight() const {
    Road right; //for right turns
    sf::Vector2f p0(0, .95 * yRes); //start point of curve
    sf::Vector2f p1(.5 * xRes, .302 * yRes); //used to shape curve
    sf::Vector2f p2(.9 * xRes, .355 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(xRes, .75 * yRes);
    p1 = sf::Vector2f(.55 * xRes, .46 * yRes);
    p2 = sf::Vector2f(.95 * xRes, .341 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes sharp left turn road
Road GameInitializer::makeSharpLeft() const {
    Road right; //for right turns
    sf::Vector2f p0(xRes, .95 * yRes); //start point of curve
    sf::Vector2f p1(.5 * xRes, .302 * yRes); //used to shape curve
    sf::Vector2f p2(.1 * xRes, .355 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(0, .75 * yRes);
    p1 = sf::Vector2f(.45 * xRes, .46 * yRes);
    p2 = sf::Vector2f(.05 * xRes, .341 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes transition animation for straight to left
RoadTransition GameInitializer::makeStraightToLeft() const {
    RoadTransition straightToLeft;
    straightToLeft.addStateVectors(0, .85 * yRes, .51 * xRes / 2, (.85 * yRes + .35 * yRes) / 2,
        .51 * xRes, .3285 * yRes);
    straightToLeft.addStateVectors(xRes, .85 * yRes, .6 * xRes, .45 * yRes, .49 * xRes, .34 * yRes);
    straightToLeft.addStateVectors(0, .8 * yRes, .4 * xRes, .45 * yRes, .24 * xRes, .342 * yRes);
    straightToLeft.addStateVectors(xRes, .9 * yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);

    return straightToLeft;
}

//makes transition animation for straight to right
RoadTransition GameInitializer::makeStraightToRight() const {
    RoadTransition straightToRight;
    straightToRight.addStateVectors(0, .85 * yRes, .51 * xRes / 2, (.85 * yRes + .35 * yRes) / 2,
        .51 * xRes, .3285 * yRes);
    straightToRight.addStateVectors(xRes, .85 * yRes, .6 * xRes, .45 * yRes, .49 * xRes, .34 * yRes);
    straightToRight.addStateVectors(0, .95 * yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    straightToRight.addStateVectors(xRes, .8 * yRes, .6 * xRes, .45 * yRes, .76 * xRes, .342 * yRes);

    return straightToRight;
}

//makes transition animation for left to straight
RoadTransition GameInitializer::makeLeftToStraight() const {
    RoadTransition l2s;
    l2s.addStateVectors(0, .8 * yRes, .4 * xRes, .45 * yRes, .24 * xRes, .342 * yRes);
    l2s.addStateVectors(xRes, .9 * yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(0, .85 * yRes, .51 * xRes / 2, (.85 * yRes + .35 * yRes) / 2,
        .51 * xRes, .3285 * yRes);
    l2s.addStateVectors(xRes, .85 * yRes, .6 * xRes, .45 * yRes, .49 * xRes, .34 * yRes);

    return l2s;
}

//makes transition animation for right to straight
RoadTransition GameInitializer::makeRightToStraight() const {
    RoadTransition r2s;
    r2s.addStateVectors(0, .95 * yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    r2s.addStateVectors(xRes, .8 * yRes, .6 * xRes, .45 * yRes, .76 * xRes, .342 * yRes);
    r2s.addStateVectors(0, .85 * yRes, .51 * xRes / 2, (.85 * yRes + .35 * yRes) / 2,
        .51 * xRes, .3285 * yRes);
    r2s.addStateVectors(xRes, .85 * yRes, .6 * xRes, .45 * yRes, .49 * xRes, .34 * yRes);

    return r2s;
}

//makes transition animation for left to sharp left
RoadTransition GameInitializer::makeLeftToSharp() const {
    RoadTransition l2s;
    l2s.addStateVectors(0, .8 * yRes, .4 * xRes, .45 * yRes, .24 * xRes, .342 * yRes);
    l2s.addStateVectors(xRes, .9 * yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(0, .75 * yRes, .45 * xRes, .46 * yRes, .05 * xRes, .341 * yRes);
    l2s.addStateVectors(xRes, .95 * yRes, .5 * xRes, .302 * yRes, .1 * xRes, .355 * yRes);

    return l2s;
}

//makes transition animation for right to sharp right
RoadTransition GameInitializer::makeRightToSharp() const {
    RoadTransition r2s;
    r2s.addStateVectors(0, .95 * yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    r2s.addStateVectors(xRes, .8 * yRes, .6 * xRes, .45 * yRes, .76 * xRes, .342 * yRes);
    r2s.addStateVectors(0, .95 * yRes, .5 * xRes, .302 * yRes, .9 * xRes, .355 * yRes);
    r2s.addStateVectors(xRes, .75 * yRes, .55 * xRes, .46 * yRes, .95 * xRes, .341 * yRes);

    return r2s;
}

//makes transition animation for sharp left to left
RoadTransition GameInitializer::makeSharpToLeft() const {
    RoadTransition l2s;
    l2s.addStateVectors(xRes, .95 * yRes, .5 * xRes, .302 * yRes, .1 * xRes, .355 * yRes);
    l2s.addStateVectors(0, .75 * yRes, .45 * xRes, .46 * yRes, .05 * xRes, .341 * yRes);
    l2s.addStateVectors(xRes, .9 * yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(0, .8 * yRes, .4 * xRes, .45 * yRes, .24 * xRes, .342 * yRes);
    

    return l2s;
}

//makes transition animation for sharp right to right
RoadTransition GameInitializer::makeSharpToRight() const {
    RoadTransition r2s;
    r2s.addStateVectors(xRes, .75 * yRes, .55 * xRes, .46 * yRes, .95 * xRes, .341 * yRes);
    r2s.addStateVectors(0, .95 * yRes, .5 * xRes, .302 * yRes, .9 * xRes, .355 * yRes);
    r2s.addStateVectors(xRes, .8 * yRes, .6 * xRes, .45 * yRes, .76 * xRes, .342 * yRes);
    r2s.addStateVectors(0, .95 * yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);

    return r2s;
}




//makes speedlines animation
SpeedLines GameInitializer::makeSpeed1Lines() const {
    SpeedLines sl(*window);

    sf::Vector2f p0(.2 * xRes, .45 * yRes);
    sf::Vector2f p1(.2 * xRes / 2, .83 * yRes / 2);
    sf::Vector2f p2(0, .38 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .45 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, .83 * yRes / 2);
    p2 = sf::Vector2f(xRes, .38 * yRes);
    sl.addCurve(p0,p1,p2);

    p0 = sf::Vector2f(.2 * xRes, .55 * yRes);
    p1 = sf::Vector2f(.2 * xRes / 2, 1.17 * yRes / 2);
    p2 = sf::Vector2f(0, .62 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .55 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, 1.17 * yRes / 2);
    p2 = sf::Vector2f(xRes, .62 * yRes);
    sl.addCurve(p0, p1, p2);

    return sl;
}
SpeedLines GameInitializer::makeSpeed2Lines() const {
    SpeedLines sl(*window);

    sf::Vector2f p0(.2 * xRes, .5 * yRes);
    sf::Vector2f p1(.2 * xRes / 2, .93 * yRes / 2);
    sf::Vector2f p2(0, .43 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .5 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, .93 * yRes / 2);
    p2 = sf::Vector2f(xRes, .43 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.2 * xRes, .5 * yRes);
    p1 = sf::Vector2f(.2 * xRes / 2, 1.07 * yRes / 2);
    p2 = sf::Vector2f(0, .57 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .5 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, 1.07 * yRes / 2);
    p2 = sf::Vector2f(xRes, .57 * yRes);
    sl.addCurve(p0, p1, p2);

    return sl;
}
SpeedLines GameInitializer::makeSpeed3Lines() const {
    SpeedLines sl(*window);

    sf::Vector2f p0(.2 * xRes, .45 * yRes);
    sf::Vector2f p1(.2 * xRes / 2, .83 * yRes / 2);
    sf::Vector2f p2(0, .38 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .45 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, .83 * yRes / 2);
    p2 = sf::Vector2f(xRes, .38 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.2 * xRes, .55 * yRes);
    p1 = sf::Vector2f(.2 * xRes / 2, 1.17 * yRes / 2);
    p2 = sf::Vector2f(0, .62 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .55 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, 1.17 * yRes / 2);
    p2 = sf::Vector2f(xRes, .62 * yRes);
    sl.addCurve(p0, p1, p2);

    return sl;
}




//makes horizon line that is very cool and complicated and worth having an initializer function
GraphicsLayer GameInitializer::makeHorizon() const {
    GraphicsLayer hor;
    hor.addLine(0, 0.35 * yRes, xRes, 0.35 * yRes);
    hor.setColor(horizonColor);

    return hor;
}


//makes background of level
GraphicsLayer GameInitializer::makeBackground() const {
    GraphicsLayer back;
    back.addLine(0, 0.35 * yRes, 100, 0.25 * yRes);
    back.addLine(100, 0.25 * yRes, 100, 0.25 * yRes);
    back.setColor(sf::Color::White);

    return back;
}




//makes sports car
Car* GameInitializer::makeSportsCar() const{
    SportsCar* car = new SportsCar();
    static sf::Texture carTexture;
    sf::IntRect spriteLocation(200, 296, 40, 40);
    if(!carTexture.loadFromFile("sportscar.png")) {
        std::cerr << "Failed to load car texture!" << std::endl;
        return nullptr;
    }
    sf::Sprite sprite(carTexture, spriteLocation);
    car->setSprite(sprite);
    car->getSprite().setPosition(xRes * .4, yRes * 0.55);
    car->getSprite().setScale(yRes * .01, yRes * .01);
    car->setYRes(yRes);
    return car;
}




//makes track1
Track GameInitializer::loadTrack1() const {
    Track track;
    track.addRoadUpdate(200, left);
    track.addRoadUpdate(300, sharpLeft);
    track.addRoadUpdate(400, left);
    track.addRoadUpdate(600, straight);
    track.addRoadUpdate(750, left);
    track.addRoadUpdate(850, straight);
    track.addRoadUpdate(950, right);
    track.addRoadUpdate(1050, sharpRight);
    track.addRoadUpdate(1200, right);
    track.addRoadUpdate(1300, straight);
    track.addRoadUpdate(1400, left);
    track.addRoadUpdate(1650, straight);
    track.addRoadUpdate(2000, finish);

    return track;
}