#include "InitializerHelper.hpp"

//constructor
InitializerHelper::InitializerHelper(sf::RenderWindow& win, float xResInit, float yResInit, sf::Color& roadColorInit,
    sf::Color& horizonColorInit, sf::Color& backgroundColorInit) {

    window = &win;
    xRes = xResInit;
    yRes = yResInit;
    roadColor = roadColorInit;
    horizonColor = horizonColorInit;
    backgroundColor = backgroundColorInit;
}




//makes straight road
Road InitializerHelper::makeStraight() const{
    Road straight; //for straight sections (must use curve for transition animations)
    sf::Vector2f p0(-.1 * xRes, yRes);
    sf::Vector2f p1(.45 * xRes / 2, 1.324 * yRes / 2);
    sf::Vector2f p2(.51 * xRes, .324 * yRes);
    straight.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(1.1 * xRes, yRes);
    p1 = sf::Vector2f(1.55 * xRes / 2, 1.324 * yRes/ 2);
    p2 = sf::Vector2f(.49 * xRes, .324 * yRes);
    straight.addCurve(p0, p1, p2);

    straight.setColor(roadColor);

    return straight;
}

//makes left turn road
Road InitializerHelper::makeLeft() const {
    Road left; //for left turns
    sf::Vector2f p0(xRes, yRes);
    sf::Vector2f p1(.62 * xRes, .32 * yRes);
    sf::Vector2f p2(.24 * xRes, .352 * yRes);
    left.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(-.15 * xRes, yRes);
    p1 = sf::Vector2f(.46 * xRes, .58 * yRes);
    p2 = sf::Vector2f(.23 * xRes, .332 * yRes);
    left.addCurve(p0, p1, p2);

    left.setColor(roadColor);

    return left;
}

//makes right turn road
Road InitializerHelper::makeRight() const {
    Road right; //for right turns
    sf::Vector2f p0(0, yRes); //start point of curve
    sf::Vector2f p1(.38 * xRes, .32 * yRes); //used to shape curve
    sf::Vector2f p2(.76 * xRes, .352 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(1.15 * xRes, yRes);
    p1 = sf::Vector2f(.54 * xRes, .58 * yRes);
    p2 = sf::Vector2f(.77 * xRes, .332 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes sharp right turn road
Road InitializerHelper::makeSharpRight() const {
    Road right; //for right turns
    sf::Vector2f p0(0.07 * xRes, yRes); //start point of curve
    sf::Vector2f p1(.45 * xRes, .32 * yRes); //used to shape curve
    sf::Vector2f p2(.92 * xRes, .353 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(1.1 * xRes, yRes);
    p1 = sf::Vector2f(.52 * xRes, .48 * yRes);
    p2 = sf::Vector2f(.97 * xRes, .34 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes sharp left turn road
Road InitializerHelper::makeSharpLeft() const {
    Road right;
    sf::Vector2f p0(.93 * xRes,yRes); //start point of curve
    sf::Vector2f p1(.55 * xRes, .32 * yRes); //used to shape curve
    sf::Vector2f p2(.08 * xRes, .353 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(-.1 * xRes,yRes);
    p1 = sf::Vector2f(.48 * xRes, .48 * yRes);
    p2 = sf::Vector2f(.03 * xRes, .34 * yRes);
    right.addCurve(p0, p1, p2);

    right.setColor(roadColor);

    return right;
}

//makes transition animation for straight to left
RoadTransition InitializerHelper::makeStraightToLeft() const {
    RoadTransition straightToLeft;
    straightToLeft.addStateVectors(-.1 * xRes, yRes, .45 * xRes / 2, 1.324 * yRes / 2, .51 * xRes, .324 * yRes);
    straightToLeft.addStateVectors(1.1 * xRes, yRes, 1.55 * xRes / 2, 1.324 * yRes / 2, .49 * xRes, .324 * yRes);
    straightToLeft.addStateVectors(-.15 * xRes, yRes, .46 * xRes, .58 * yRes, .23 * xRes, .332 * yRes);
    straightToLeft.addStateVectors(xRes, yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);

    return straightToLeft;
}

//makes transition animation for straight to right
RoadTransition InitializerHelper::makeStraightToRight() const {
    RoadTransition straightToRight;
    straightToRight.addStateVectors(-.1 * xRes, yRes, .45 * xRes / 2, 1.324 * yRes / 2, .51 * xRes, .324 * yRes);
    straightToRight.addStateVectors(1.1 * xRes, yRes, 1.55 * xRes / 2, 1.324 * yRes / 2, .49 * xRes, .324 * yRes);
    straightToRight.addStateVectors(0, yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    straightToRight.addStateVectors(1.15 * xRes, yRes, .54 * xRes, .58 * yRes, .77 * xRes, .332 * yRes);

    return straightToRight;
}

//makes transition animation for left to straight
RoadTransition InitializerHelper::makeLeftToStraight() const {
    RoadTransition l2s;
    l2s.addStateVectors(-.15 * xRes, yRes, .46 * xRes, .58 * yRes, .23 * xRes, .332 * yRes);
    l2s.addStateVectors(xRes, yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(-.1 * xRes, yRes, .45 * xRes / 2, 1.324 * yRes / 2, .51 * xRes, .324 * yRes);
    l2s.addStateVectors(1.1 * xRes, yRes, 1.55 * xRes / 2, 1.324 * yRes / 2, .49 * xRes, .324 * yRes);

    return l2s;
}

//makes transition animation for right to straight
RoadTransition InitializerHelper::makeRightToStraight() const {
    RoadTransition r2s;
    r2s.addStateVectors(0, yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    r2s.addStateVectors(1.15 * xRes, yRes, .54 * xRes, .58 * yRes, .77 * xRes, .332 * yRes);
    r2s.addStateVectors(-.1 * xRes, yRes, .45 * xRes / 2, 1.324 * yRes / 2, .51 * xRes, .324 * yRes);
    r2s.addStateVectors(1.1 * xRes, yRes, 1.55 * xRes / 2, 1.324 * yRes / 2, .49 * xRes, .324 * yRes);

    return r2s;
}

//makes transition animation for left to sharp left
RoadTransition InitializerHelper::makeLeftToSharp() const {
    RoadTransition l2s;
    l2s.addStateVectors(-.15 * xRes, yRes, .46 * xRes, .58 * yRes, .23 * xRes, .332 * yRes);
    l2s.addStateVectors(xRes, yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(-.1 * xRes, yRes, .48 * xRes, .48 * yRes, .03 * xRes, .34 * yRes);
    l2s.addStateVectors(.93 * xRes, yRes, .55 * xRes, .32 * yRes, .08 * xRes, .353 * yRes);

    return l2s;
}

//makes transition animation for right to sharp right
RoadTransition InitializerHelper::makeRightToSharp() const {
    RoadTransition r2s;
    r2s.addStateVectors(0, yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    r2s.addStateVectors(1.15 * xRes, yRes, .54 * xRes, .58 * yRes, .77 * xRes, .332 * yRes);
    r2s.addStateVectors(0.07 * xRes, yRes, .45 * xRes, .32 * yRes, .92 * xRes, .353 * yRes);
    r2s.addStateVectors(1.1 * xRes, yRes, .52 * xRes, .48 * yRes, .97 * xRes, .34 * yRes);

    return r2s;
}

//makes transition animation for sharp left to left
RoadTransition InitializerHelper::makeSharpToLeft() const {
    RoadTransition l2s;
    l2s.addStateVectors(.93 * xRes, yRes, .55 * xRes, .32 * yRes, .08 * xRes, .353 * yRes);
    l2s.addStateVectors(-.1 * xRes, yRes, .48 * xRes, .48 * yRes, .03 * xRes, .34 * yRes);
    l2s.addStateVectors(xRes, yRes, .62 * xRes, .32 * yRes, .24 * xRes, .352 * yRes);
    l2s.addStateVectors(-.15 * xRes, yRes, .46 * xRes, .58 * yRes, .23 * xRes, .332 * yRes);

    return l2s;
}

//makes transition animation for sharp right to right
RoadTransition InitializerHelper::makeSharpToRight() const {
    RoadTransition r2s;
    r2s.addStateVectors(0.07 * xRes, yRes, .45 * xRes, .32 * yRes, .92 * xRes, .353 * yRes);
    r2s.addStateVectors(1.1 * xRes, yRes, .52 * xRes, .48 * yRes, .97 * xRes, .34 * yRes);
    r2s.addStateVectors(0, yRes, .38 * xRes, .32 * yRes, .76 * xRes, .352 * yRes);
    r2s.addStateVectors(1.15 * xRes, yRes, .54 * xRes, .58 * yRes, .77 * xRes, .332 * yRes);

    return r2s;
}




//makes speedlines animation
SpeedLines InitializerHelper::makeSpeed1Lines() const {
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
SpeedLines InitializerHelper::makeSpeed2Lines() const {
    SpeedLines sl(*window);
    float centerView = window->getView().getCenter().x;

    sf::Vector2f p0(.2 * xRes, .4 * yRes);
    sf::Vector2f p1(.2 * xRes / 2, .73 * yRes / 2);
    sf::Vector2f p2(0, .33 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.8 * xRes, .4 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, .73 * yRes / 2);
    p2 = sf::Vector2f(xRes, .33 * yRes);
    sl.addCurve(p0, p1, p2);

    p0 = sf::Vector2f(.2 * xRes, .6 * yRes);
    p1 = sf::Vector2f(.2 * xRes / 2, 1.27 * yRes / 2);
    p2 = sf::Vector2f(0, .67 * yRes);
    sl.addCurve(p0, p1, p2);  

    p0 = sf::Vector2f(.8 * xRes, .6 * yRes);
    p1 = sf::Vector2f(1.8 * xRes / 2, 1.27 * yRes / 2);
    p2 = sf::Vector2f(xRes, .67 * yRes);
    sl.addCurve(p0, p1, p2);

    return sl;
}
SpeedLines InitializerHelper::makeSpeed3Lines() const {
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
GraphicsLayer InitializerHelper::makeHorizon() const {
    GraphicsLayer hor;
    hor.addLine(-xRes, 0.35 * yRes, 2 * xRes, 0.35 * yRes);
    hor.setColor(horizonColor);

    return hor;
}
 

//makes background of level1
GraphicsLayer InitializerHelper::makeBackground1() const {
    GraphicsLayer back;

    back.addLine(-.25 * xRes, 0.35 * yRes, 0, 0.25 * yRes);
    back.addLine(0, 0.25 * yRes, .25 * xRes, 0.35 * yRes);
    back.addLine(.25 * xRes, 0.35 * yRes, .5 * xRes, 0.25 * yRes);
    back.addLine(.5 * xRes, 0.25 * yRes, .75 * xRes, 0.35 * yRes);
    back.addLine(.75 * xRes, 0.35 * yRes, xRes, 0.25 * yRes);
    back.addLine(xRes, 0.25 * yRes, 1.25 * xRes, 0.35 * yRes);

    back.addLine(.1 * xRes,  .29 * yRes, .25 * xRes, 0.15 * yRes);
    back.addLine(.25 * xRes, .15 * yRes, .4 * xRes, 0.29 * yRes);
    back.addLine(.6 * xRes, .29 * yRes, .75 * xRes, 0.15 * yRes);
    back.addLine(.75 * xRes, .15 * yRes, .9 * xRes, 0.29 * yRes);

    back.setColor(backgroundColor);
    return back;
}

//makes background of level2
GraphicsLayer InitializerHelper::makeBackground2() const {
    GraphicsLayer back;

    back.addLine(-.2 * xRes, 0.35 * yRes, -.2 * xRes, 0.28 * yRes);
    back.addLine(-.2 * xRes, 0.28 * yRes, -.12 * xRes, 0.28 * yRes);
    back.addLine(-.12 * xRes, 0.28 * yRes, -.12 * xRes, 0.35 * yRes);
    back.addLine(.2 * xRes, 0.35 * yRes, .2 * xRes, 0.28 * yRes);
    back.addLine(.2 * xRes, 0.28 * yRes, .28 * xRes, 0.28 * yRes);
    back.addLine(.28 * xRes, 0.28 * yRes, .28 * xRes, 0.35 * yRes);
    back.addLine(.8 * xRes, 0.35 * yRes, .8 * xRes, 0.28 * yRes);
    back.addLine(.8 * xRes, 0.28 * yRes, .88 * xRes, 0.28 * yRes);
    back.addLine(.88 * xRes, 0.28 * yRes, .88 * xRes, 0.35 * yRes);
    back.addLine(1.12 * xRes, 0.35 * yRes, 1.12 * xRes, 0.28 * yRes);
    back.addLine(1.12 * xRes, 0.28 * yRes, 1.2 * xRes, 0.28 * yRes);
    back.addLine(1.2 * xRes, 0.28 * yRes, 1.2 * xRes, 0.35 * yRes);

    back.addLine(0, 0.35 * yRes, 0, 0.24 * yRes);
    back.addLine(0, 0.24 * yRes, .1 * xRes, 0.24 * yRes);
    back.addLine(.1 * xRes, 0.24 * yRes, .1 * xRes, 0.35 * yRes);
    back.addLine(xRes, 0.35 * yRes, xRes, 0.24 * yRes);
    back.addLine(xRes, 0.24 * yRes, .9 * xRes, 0.24 * yRes);
    back.addLine(.9 * xRes, 0.24 * yRes, .9 * xRes, 0.35 * yRes);

    back.addLine(.3 * xRes, 0.35 * yRes, .3 * xRes, 0.08 * yRes);
    back.addLine(.3 * xRes, 0.08 * yRes, .4 * xRes, 0.08 * yRes);
    back.addLine(.4 * xRes, 0.08 * yRes, .4 * xRes, 0.35 * yRes);

    back.addLine(.82 * xRes, 0.28 * yRes, .82 * xRes, 0.08 * yRes);
    back.addLine(.82 * xRes, 0.08 * yRes, .92 * xRes, 0.08 * yRes);
    back.addLine(.92 * xRes, 0.08 * yRes, .92 * xRes, 0.24 * yRes);

    back.addLine(.6 * xRes, 0.288 * yRes, .6 * xRes, 0.015 * yRes);
    back.addLine(.6 * xRes, 0.015 * yRes, .67 * xRes, 0.015 * yRes);
    back.addLine(.67 * xRes, 0.015 * yRes, .67 * xRes, 0.35 * yRes);

    sf::Vector2f p1(.46 * xRes, .35 * yRes);
    sf::Vector2f p2(.61 * xRes, .2 * yRes);
    sf::Vector2f p3(.63 * xRes, .365 * yRes);
    back.addCurve(p1, p2, p3);

    back.setColor(backgroundColor);
    return back;
}



//initializes passing objects on the sides
MovingObject InitializerHelper::makeTrack1Move1() const {
    MovingObject gr;
    gr.addLine(.25 * xRes, .36 * yRes, .26 * xRes, .35 * yRes);
    gr.addLine(.26 * xRes, .35 * yRes, .265 * xRes, .356 * yRes);
    gr.addLine(.265 * xRes, .356 * yRes, .272 * xRes, .36 * yRes);
    gr.addLine(.25 * xRes, .36 * yRes, .272 * xRes, .36 * yRes);

    gr.setColor(horizonColor);
    gr.xRes = xRes;
    gr.position = -1;
    return gr;
}
MovingObject InitializerHelper::makeTrack1Move2() const {
    MovingObject gr;

    gr.addLine(.75 * xRes, .36 * yRes, .76 * xRes, .35 * yRes);
    gr.addLine(.76 * xRes, .35 * yRes, .765 * xRes, .356 * yRes);
    gr.addLine(.765 * xRes, .356 * yRes, .772 * xRes, .36 * yRes);
    gr.addLine(.75 * xRes, .36 * yRes, .772 * xRes, .36 * yRes);

    gr.setColor(horizonColor);
    gr.xRes = xRes;
    gr.position = 1;
    return gr;
}

MovingObject InitializerHelper::makeTrack2Move1() const {
    MovingObject gr;
    gr.addLine(.25 * xRes, .36 * yRes, .26 * xRes, .35 * yRes);
    gr.addLine(.26 * xRes, .35 * yRes, .265 * xRes, .356 * yRes);
    gr.addLine(.265 * xRes, .356 * yRes, .272 * xRes, .36 * yRes);
    gr.addLine(.25 * xRes, .36 * yRes, .272 * xRes, .36 * yRes);

    gr.setColor(horizonColor);
    gr.xRes = xRes;
    gr.position = -1;
    return gr;
}
MovingObject InitializerHelper::makeTrack2Move2() const {
    MovingObject gr;

    gr.addLine(.75 * xRes, .36 * yRes, .76 * xRes, .35 * yRes);
    gr.addLine(.76 * xRes, .35 * yRes, .765 * xRes, .356 * yRes);
    gr.addLine(.765 * xRes, .356 * yRes, .772 * xRes, .36 * yRes);
    gr.addLine(.75 * xRes, .36 * yRes, .772 * xRes, .36 * yRes);

    gr.setColor(horizonColor);
    gr.xRes = xRes;
    gr.position = 1;
    return gr;
}




MovingObject InitializerHelper::makeFinishLine() const {
    MovingObject finish;

    sf::Vector2f p1(.48 * xRes, .36 * yRes);
    sf::Vector2f p2(.52 * xRes, .36 * yRes);
    finish.addLine(p1, p2);

    p1 = sf::Vector2f(.47 * xRes, .367 * yRes);
    p2 = sf::Vector2f(.53 * xRes, .367 * yRes);
    finish.addLine(p1, p2);

    finish.setColor(roadColor);
    finish.position = 0;
    return finish;
}





//makes sports car
Car* InitializerHelper::makeSportsCar() const{
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

//makes safety car
Car* InitializerHelper::makeSafetyCar() const {
    SafetyCar* car = new SafetyCar();
    static sf::Texture carTexture;
    sf::IntRect spriteLocation(200, 296, 40, 40);
    if (!carTexture.loadFromFile("safetycar.png")) {
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

//makes cop car
Car* InitializerHelper::makeCopCar() const {
    CopCar* car = new CopCar();
    static sf::Texture carTexture;
    sf::IntRect spriteLocation(200, 296, 40, 40);
    if (!carTexture.loadFromFile("copcar.png")) {
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
Track InitializerHelper::loadTrack1(std::string& musicFilePath) const {

    musicFilePath = "RaceToMars.mp3";

    Track track;

    track.addRoadUpdate(150, left);
    track.addRoadUpdate(300, sharpLeft);
    track.addRoadUpdate(400, left);
    track.addRoadUpdate(600, straight);
    track.addRoadUpdate(750, left);
    track.addRoadUpdate(850, straight);
    track.addRoadUpdate(950, right);
    track.addRoadUpdate(1050, sharpRight);
    track.addRoadUpdate(1220, right);
    track.addRoadUpdate(1460, straight);
    track.addRoadUpdate(1600, finish);
    return track;
}

//makes track2
Track InitializerHelper::loadTrack2(std::string& musicFilePath) const {

    musicFilePath = "CrashLanding.mp3";

    Track track;

    track.addRoadUpdate(80, right);
    track.addRoadUpdate(180, straight);
    track.addRoadUpdate(280, left);
    track.addRoadUpdate(380, sharpLeft);
    track.addRoadUpdate(580, left);
    track.addRoadUpdate(670, straight);
    track.addRoadUpdate(750, right);
    track.addRoadUpdate(840, sharpRight);
    track.addRoadUpdate(1100, right);
    track.addRoadUpdate(1200, straight);
    track.addRoadUpdate(1290, left);
    track.addRoadUpdate(1380, sharpLeft);
    track.addRoadUpdate(1490, left);
    track.addRoadUpdate(1560, straight);
    track.addRoadUpdate(1650, finish);

    return track;
}