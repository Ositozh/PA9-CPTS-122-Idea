#include "includes.hpp"

int main() {
    const int frames = 12;
    const float yRes = 1080;
    float xRes = 16.0 / 9 * yRes;
    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "PA9 Graphics");
    sf::Clock clock; //for time normalization


    //Music Stuff
    /*
    sf::Music music;
    music.openFromFile("");
    music.setLoop(true);
    music.play();
    */


    //Colors
    sf::Color roadColor(220, 50, 50);
    sf::Color horizonColor(160, 50, 200);



    //initialization of game items
    GameInitializer initializer(window, xRes, yRes, roadColor, horizonColor, horizonColor);
    Road straightRoad = initializer.makeStraight();
    Road leftRoad = initializer.makeLeft();
    Road rightRoad = initializer.makeRight();
    Road sharpLeftRoad = initializer.makeSharpLeft();
    Road sharpRightRoad = initializer.makeSharpRight();
    GraphicsLayer horizonLine = initializer.makeHorizon();
    GraphicsLayer background = initializer.makeBackground();


    //initialize animations
    RoadTransition straightToLeft = initializer.makeStraightToLeft();
    RoadTransition straightToRight = initializer.makeStraightToRight();
    RoadTransition leftToStraight = initializer.makeLeftToStraight();
    RoadTransition rightToStraight = initializer.makeRightToStraight();
    RoadTransition leftToSharp = initializer.makeLeftToSharp();
    RoadTransition rightToSharp = initializer.makeRightToSharp();
    RoadTransition sharpToLeft = initializer.makeSharpToLeft();
    RoadTransition sharpToRight = initializer.makeSharpToRight();

    SpeedLines straightMoving(window);
    SpeedLines speed1 = initializer.makeSpeed1Lines();
    SpeedLines speed2 = initializer.makeSpeed2Lines();
    //SpeedLines speed3 = initializer.makeSpeed3Lines();

    AnimationsHandler roadTransitionsHandler(frames, frames * 1.5);
    roadTransitionsHandler.add(&straightToLeft);
    roadTransitionsHandler.add(&straightToRight);
    roadTransitionsHandler.add(&leftToStraight);
    roadTransitionsHandler.add(&leftToSharp);
    roadTransitionsHandler.add(&rightToStraight);
    roadTransitionsHandler.add(&rightToSharp);
    roadTransitionsHandler.add(&sharpToLeft);
    roadTransitionsHandler.add(&sharpToRight);

    AnimationsHandler speedLinesHandler(frames, frames * 3);
    speedLinesHandler.add(&speed1);
    speedLinesHandler.add(&speed2);
    //speedLinesHandler.add(&speed3);


    //will be initialized during game depending on player selection
    Track track = initializer.loadTrack1();
    track.setCurrentState(straight);
    Car* car = initializer.makeSportsCar();
    car->setSpeed(4);

    


    float deltaTime, totalTime = 0, penaltyCooldown = 0, updateDistanceTime = 0, distance = 0;
    int trackIndex = 0;
    bool inAnimation = false; //indicates if a road animation is currently playing

    // Track out-of-bounds count and time penalty
    int outOfBoundsCount = 0;
    sf::Time timePenalty = sf::seconds(0);

    // Lap timer variables
    auto lapStartTime = std::chrono::steady_clock::now();
    auto lapEndTime = std::chrono::steady_clock::now();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))

    {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }
    sf::Text lapTimeText;
    lapTimeText.setFont(font);
    lapTimeText.setCharacterSize(20);
    lapTimeText.setFillColor(sf::Color::White);
    lapTimeText.setPosition(xRes * 0.42, 10.0f);

    sf::Text timePenaltyText;
    timePenaltyText.setFont(font);
    timePenaltyText.setCharacterSize(20);
    timePenaltyText.setFillColor(sf::Color::White);
    timePenaltyText.setPosition(xRes * 0.5, 10.0f);





    //MAIN GAME LOOP MAIN GAME LOOP
    while (window.isOpen()) //MAIN GAME LOOP MAIN GAME LOOP
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                delete car; //needed since new was used by initializer
                break;
            }
        }

        //handle keyboard input (allows wasd and arrowkeys)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            car->update(sf::Keyboard::Up, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            car->update(sf::Keyboard::Left, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            car->update(sf::Keyboard::Down, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            car->update(sf::Keyboard::Right, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            car->update(sf::Keyboard::Up, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            car->update(sf::Keyboard::Left, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            car->update(sf::Keyboard::Down, deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            car->update(sf::Keyboard::Right, deltaTime);


        //updates clock for animations and distance
        deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        updateDistanceTime += deltaTime;

        //update distance
        if (updateDistanceTime >= 0.05) {
            distance += car->getSpeed() / 2;
            updateDistanceTime = 0;
        }

        //updates road according to track
        if (track.getDistances()[trackIndex] <= distance) {
            if (track.getCurrentState() == straight) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    window.close();
                    break;
                }
                if (track.getCurrentState() == left) {
                    straightToLeft.toggle();
                }
                else {
                    straightToRight.toggle();
                }
            }
            else if (track.getCurrentState() == left) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    window.close();
                    break;
                }
                if (track.getCurrentState() == straight) {
                    leftToStraight.toggle();
                }
                else {
                    leftToSharp.toggle();
                }
            }
            else if (track.getCurrentState() == right) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    window.close();
                    break;
                }
                if (track.getCurrentState() == left) {
                    rightToStraight.toggle();
                }
                else {
                    rightToSharp.toggle();
                }
            }
            else if (track.getCurrentState() == sharpLeft) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    window.close();
                    break;
                }
                sharpToLeft.toggle();
            }
            else {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    window.close();
                    break;
                }
                sharpToRight.toggle();
            }
            inAnimation = true;
            trackIndex++;
        }
        window.clear();

        //keeps track of when roads are transition to display them correctly
        if (inAnimation) {
            if (straightToLeft.isOn()) {
                if (straightToLeft.getFrame() == frames) {
                    straightToLeft.toggle();
                }
            }
            else if (straightToRight.isOn()) {
                if (straightToRight.getFrame() == frames) {
                    straightToRight.toggle();
                }
            }
            else if (leftToStraight.isOn()) {
                if (leftToStraight.getFrame() == frames) {
                    leftToStraight.toggle();
                }
            }
            else if (rightToStraight.isOn()) {
                if (rightToStraight.getFrame() == frames) {
                    rightToStraight.toggle();
                }
            }
            else if (sharpToLeft.isOn()) {
                if (sharpToLeft.getFrame() == frames) {
                    sharpToLeft.toggle();
                }
            }
            else if (sharpToRight.isOn()) {
                if (sharpToRight.getFrame() == frames) {
                    sharpToRight.toggle();
                }
            }
            else if (leftToSharp.isOn()) {
                if (leftToSharp.getFrame() == frames) {
                    leftToSharp.toggle();
                }
            }
            else if (rightToSharp.isOn()) {
                if (rightToSharp.getFrame() == frames) {
                    rightToSharp.toggle();
                }
            }
            else {
                if (track.getCurrentState() == straight) {
                    straightRoad.draw(window);
                }
                else if (track.getCurrentState() == left) {
                    leftRoad.draw(window);
                }
                else if (track.getCurrentState() == right) {
                    rightRoad.draw(window);
                }
                inAnimation = false;
            }
        }
        else { //display stationary road state (no road transition is active)
            if (track.getCurrentState() == straight) {
                if (!straightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)
                    || !straightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)) {
                    penaltyCooldown += deltaTime;
                    if (penaltyCooldown >= 0.3) {
                        applyTimePenalty(outOfBoundsCount, timePenalty);
                        penaltyCooldown = 0;
                    }
                }
                straightRoad.draw(window);
            }
            else if (track.getCurrentState() == left) {
                if (!leftRoad.carOnRoad(car->getSprite().getPosition().x, yRes)
                    || !leftRoad.carOnRoad(car->getSprite().getPosition().x, yRes)) {
                    penaltyCooldown += deltaTime;
                    if (penaltyCooldown >= 0.3) {
                        applyTimePenalty(outOfBoundsCount, timePenalty);
                        penaltyCooldown = 0;
                    }
                }
                leftRoad.draw(window);
            }
            else if (track.getCurrentState() == right) {
                if (!rightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)
                    || !rightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)) {
                    penaltyCooldown += deltaTime;
                    if (penaltyCooldown >= 0.3) {
                        applyTimePenalty(outOfBoundsCount, timePenalty);
                        penaltyCooldown = 0;
                    }
                }
                rightRoad.draw(window);
            }
            else if (track.getCurrentState() == sharpLeft) {
                if (!sharpLeftRoad.carOnRoad(car->getSprite().getPosition().x, yRes)
                    || !sharpLeftRoad.carOnRoad(car->getSprite().getPosition().x, yRes)) {
                    penaltyCooldown += deltaTime;
                    if (penaltyCooldown >= 0.3) {
                        applyTimePenalty(outOfBoundsCount, timePenalty);
                        penaltyCooldown = 0;
                    }
                }
                sharpLeftRoad.draw(window);
            }
            else if (track.getCurrentState() == sharpRight) {
                if (!sharpRightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)
                    || !sharpRightRoad.carOnRoad(car->getSprite().getPosition().x, yRes)) {
                    penaltyCooldown += deltaTime;
                    if (penaltyCooldown >= 0.3) {
                        applyTimePenalty(outOfBoundsCount, timePenalty);
                        penaltyCooldown = 0;
                    }
                }
                sharpRightRoad.draw(window);
            }
        }

        //check car speed to play correct speedlines animation
        if (car->getSpeed() > 2) {
            speed1.setOn();
        }
        else speed1.setOff();
        if (car->getSpeed() > 4) {
            speed2.setOn();
        }
        else speed2.setOff();



        //update animations before drawing them
        roadTransitionsHandler.updateFrames(deltaTime);

        speedLinesHandler.updateFrames(deltaTime); //also draws


        //set updated road animations back to road color
        straightToLeft.setColor(roadColor);
        straightToRight.setColor(roadColor);
        leftToStraight.setColor(roadColor);
        rightToStraight.setColor(roadColor);
        leftToSharp.setColor(roadColor);
        rightToSharp.setColor(roadColor);
        sharpToLeft.setColor(roadColor);
        sharpToRight.setColor(roadColor);


        //draw everything to be on screen
        roadTransitionsHandler.draw(window);
        horizonLine.draw(window);
        car->draw(window);


        updateLapTimer(lapStartTime, lapEndTime);
        displayLapTime(window, lapStartTime, lapEndTime, font, lapTimeText);
        displayPenaltyTime(window, timePenalty, font, timePenaltyText);

        window.display();
    }


    return 0;
}