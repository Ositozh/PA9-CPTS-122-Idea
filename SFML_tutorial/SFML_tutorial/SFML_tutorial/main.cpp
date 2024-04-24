#include "includes.hpp"

int main() {
    const int frames = 20;
    const float yRes = 1080;
    float xRes = 16.0 / 9 * yRes;
    sf::Clock clock;




    //initialization of track-depended game items

    sf::Color roadColor;
    sf::Color horizonColor;
    sf::Color backgroundColor;
    sf::Music music;

    Track track;
    Car* car;
    int trackChoice = 0, carChoice = 0;
    std::string musicFilePath;
    GraphicsLayer background;
    MovingObject move1;
    MovingObject move2;
    bool runGame;


    while (trackChoice < 1 || trackChoice > 2 || carChoice < 1 || carChoice > 3) {
        runGame = consoleMenu(trackChoice, carChoice);
    }
    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "PA9 Graphics");

    if (trackChoice == 1) {
        roadColor = sf::Color(220, 0, 60);
        horizonColor = sf::Color(180, 35, 130);
        backgroundColor = sf::Color(190, 0, 180);
    }
    else {
        roadColor = sf::Color(60, 0, 200);
        horizonColor = sf::Color(40, 96, 210);
        backgroundColor = sf::Color(30, 60, 230);
    }
    //make initializer using selected colors, then assign track and music
    InitializerHelper helper(window, xRes, yRes, roadColor, horizonColor, backgroundColor);
    if (trackChoice == 1) {
        track = helper.loadTrack1(musicFilePath);
        background = helper.makeBackground1();
        move1 = helper.makeTrack1Move1();
        move2 = helper.makeTrack1Move2();
    }
    else {
        track = helper.loadTrack2(musicFilePath);
        background = helper.makeBackground2();
        move1 = helper.makeTrack2Move1();
        move2 = helper.makeTrack2Move2();
    }
    //initialize car based on selection
    if (carChoice == 1) car = helper.makeSportsCar();
    else if (carChoice == 2) car = helper.makeSafetyCar();
    else car = helper.makeCopCar();

    track.setCurrentState(straight);
    car->setSpeed(2);
    music.openFromFile(musicFilePath);
    music.setLoop(true);
    music.setVolume(8);
    music.play();

    AnimationsHandler movingObjectsHandler(frames * 6, frames * 2);
    movingObjectsHandler.add(&move1);
    movingObjectsHandler.add(&move2);

    //initialization of non track-dependent game items
    Road straightRoad = helper.makeStraight();
    Road leftRoad = helper.makeLeft();
    Road rightRoad = helper.makeRight();
    Road sharpLeftRoad = helper.makeSharpLeft();
    Road sharpRightRoad = helper.makeSharpRight();
    GraphicsLayer horizonLine = helper.makeHorizon();



    //initialize animations
    RoadTransition straightToLeft = helper.makeStraightToLeft();
    RoadTransition straightToRight = helper.makeStraightToRight();
    RoadTransition leftToStraight = helper.makeLeftToStraight();
    RoadTransition rightToStraight = helper.makeRightToStraight();
    RoadTransition leftToSharp = helper.makeLeftToSharp();
    RoadTransition rightToSharp = helper.makeRightToSharp();
    RoadTransition sharpToLeft = helper.makeSharpToLeft();
    RoadTransition sharpToRight = helper.makeSharpToRight();

    SpeedLines speed1 = helper.makeSpeed1Lines();
    SpeedLines speed2 = helper.makeSpeed2Lines();
    SpeedLines speed3 = helper.makeSpeed3Lines();

    AnimationsHandler roadTransitionsHandler(frames, frames * 1.5);
    roadTransitionsHandler.add(&straightToLeft);
    roadTransitionsHandler.add(&straightToRight);
    roadTransitionsHandler.add(&leftToStraight);
    roadTransitionsHandler.add(&leftToSharp);
    roadTransitionsHandler.add(&rightToStraight);
    roadTransitionsHandler.add(&rightToSharp);
    roadTransitionsHandler.add(&sharpToLeft);
    roadTransitionsHandler.add(&sharpToRight);

    AnimationsHandler speedLinesHandler(frames * 2, frames * 8);
    speedLinesHandler.add(&speed1);
    speedLinesHandler.add(&speed2);
    speedLinesHandler.add(&speed3);

    MovingObject finishLine = helper.makeFinishLine();
    movingObjectsHandler.add(&finishLine);

    


    float deltaTime, totalTime = 0, penaltyCooldown = 0, updateDistanceTime = 0, showMovetime = 0, distance = 0;
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



    sf::View fixedView(sf::FloatRect(0,0,xRes, yRes));
    sf::View gameView;

    int moveNumber = 1; //for moving objects

    //MAIN GAME LOOP
    while (window.isOpen() && runGame)
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


        //updates clock for animations and distance
        deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        updateDistanceTime += deltaTime;

        //update distance
        if (updateDistanceTime >= 0.1) {
            distance += car->getSpeed() / .8;
            updateDistanceTime = 0;
        }

        //updates road according to track
        if (track.getDistances()[trackIndex] <= distance && track.getCurrentState() != finish) {
            if (track.getCurrentState() == straight) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == finish) {
                    finishLine.setOn();
                }
                else if (track.getCurrentState() == left) {
                    straightToLeft.toggle();
                }
                else {
                    straightToRight.toggle();
                }
            }
            else if (track.getCurrentState() == left) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == straight) {
                    leftToStraight.toggle();
                }
                else {
                    leftToSharp.toggle();
                }
            }
            else if (track.getCurrentState() == right) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                if (track.getCurrentState() == straight) {
                    rightToStraight.toggle();
                }
                else {
                    rightToSharp.toggle();
                }
            }
            else if (track.getCurrentState() == sharpLeft) {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                sharpToLeft.toggle();
            }
            else {
                track.setCurrentState(track.getRoadStates()[trackIndex]);
                sharpToRight.toggle();
            }
            if (track.getCurrentState() != finish) {
                inAnimation = true;
                trackIndex++;
            }
        }
        else if (track.getCurrentState() == finish) {
            if (finishLine.getLines()[0].position.y >= .64 * yRes) {
                window.close();
                system("cls");
                std::cout << lapTimeText.getString().toAnsiString() <<
                    std::endl << timePenaltyText.getString().toAnsiString();
                break;
            }
        }
        window.clear();

        //keeps track of when roads are in transition to display them correctly
        if (inAnimation) {
            if (straightToLeft.isOn()) {
                if (straightToLeft.getFrame() == frames) {
                    straightToLeft.toggle();
                }
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / 4, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 4, 0);
                }
            }
            else if (straightToRight.isOn()) {
                if (straightToRight.getFrame() == frames) {
                    straightToRight.toggle();
                }
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / -4, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -4, 0);
                }
            }
            else if (leftToStraight.isOn()) {
                if (leftToStraight.getFrame() == frames) {
                    leftToStraight.toggle();
                }
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / 4, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 4, 0);
                }
            }
            else if (rightToStraight.isOn()) {
                if (rightToStraight.getFrame() == frames) {
                    rightToStraight.toggle();
                }
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / -4, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -4, 0);
                }
            }
            else if (sharpToLeft.isOn()) {
                if (sharpToLeft.getFrame() == frames) {
                    sharpToLeft.toggle();
                }
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / 1.7, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 1.7, 0);
                }
            }
            else if (sharpToRight.isOn()) {
                if (sharpToRight.getFrame() == frames) {
                    sharpToRight.toggle();
                }
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / -1.7, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -1.7, 0);
                }
            }
            else if (leftToSharp.isOn()) {
                if (leftToSharp.getFrame() == frames) {
                    leftToSharp.toggle();
                }
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / 1.7, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 1.7, 0);
                }
            }
            else if (rightToSharp.isOn()) {
                if (rightToSharp.getFrame() == frames) {
                    rightToSharp.toggle();
                }
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / -1.7, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -1.7, 0);
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
            if (track.getCurrentState() == straight
                 || track.getCurrentState() == finish) {
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
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / 2, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 2, 0);
                }
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
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / -2, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -2, 0);
                }
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
                if (car->getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
                    car->getSprite().move(car->getSpeed() / 1.25, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / 1.25, 0);
                }
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
                if (car->getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
                    car->getSprite().move(car->getSpeed() / -1.25, 0);
                    updateView(window, window.getView().getCenter().x + car->getSpeed() / -1.25, 0);
                }
            }
        }

        //check car speed to play correct speedlines animation
        if (car->getSpeed() > 3.3) {
            speed1.setOn();
        }
        else speed1.setOff();
        if (car->getSpeed() > 4.1) {
            speed2.setOn();
        }
        else speed2.setOff();
        if (car->getSpeed() > 6) {
            speed3.setOn();
        }
        
        //moving objects on sides of road
        showMovetime += deltaTime;
        if (showMovetime > 4) {
            if (moveNumber == 1) {
                move1.setOn();
                moveNumber = 2;             
            }
            else {
               move2.setOn();
               moveNumber = 1;
            }
            showMovetime = 0;
        }
        movingObjectsHandler.setFrameRate(car->getSpeed() * 3 + frames / 2);
        movingObjectsHandler.updateFrames(deltaTime);

        if (move1.isOn() && track.getCurrentState() == sharpLeft) {
            if(move1.getFrame() < 2) move1.shiftX(-xRes * .008);
        }
        if (move2.isOn() && track.getCurrentState() == sharpRight) {
            if (move2.getFrame() < 2) move2.shiftX(xRes * .008);
        }



        //update road animations before drawing them
        roadTransitionsHandler.updateFrames(deltaTime);

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
        background.draw(window);
        roadTransitionsHandler.draw(window);
        movingObjectsHandler.draw(window);
        horizonLine.draw(window);
        car->draw(window);


        //adjust view based on car movement
        updateView(window, car->getSprite().getPosition().x + (yRes * .2), xRes * 0.09);


        //timers and speed lines don't move with game
        timePenaltyText.setPosition(window.getView().getCenter().x, 10.0f);
        lapTimeText.setPosition(window.getView().getCenter().x - 150, 10.0f);
        gameView = window.getView();
        window.setView(fixedView);
        speedLinesHandler.updateFrames(deltaTime);
        window.setView(gameView);

        //update displayed timers
        updateLapTimer(lapStartTime, lapEndTime);
        displayLapTime(window, lapStartTime, lapEndTime, font, lapTimeText);
        displayPenaltyTime(window, timePenalty, font, timePenaltyText);


        window.display();
    }


    return 0;
}