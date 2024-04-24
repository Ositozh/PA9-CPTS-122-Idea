#include "includes.hpp"

int main() {
    const int frames = 12;
    const float yRes = 1080;
    float xRes = 16.0 / 9 * yRes;
    sf::Clock clock;

    //game initialization

    sf::Color roadColor;
    sf::Color horizonColor;
    sf::Music music;

    Track track;
    Car* car;
    int trackChoice = 0, carChoice = 0;
    std::string musicFilePath;
    bool runGame;


    while (trackChoice < 1 || trackChoice > 2 || carChoice < 1 || carChoice > 3) {
        runGame = consoleMenu(trackChoice, carChoice);
    }
    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "PA9 Graphics");

    if (trackChoice == 1) {
        roadColor = sf::Color(220, 40, 60);
        horizonColor = sf::Color(160, 40, 200);
    }
    else {
        roadColor = sf::Color(40, 40, 220);
        horizonColor = sf::Color(100, 0, 210);
    }
    //make initializer using selected colors, then assign track and music
    GameInitializer initializer(window, xRes, yRes, roadColor, horizonColor, horizonColor);
    if (trackChoice == 1) {
        track = initializer.loadTrack1(musicFilePath);
    }
    else {
        track = initializer.loadTrack2(musicFilePath);
    }
    //initialize car based on selection
    if (carChoice == 1) car = initializer.makeSportsCar();
    else if (carChoice == 2) car = initializer.makeSafetyCar();
    else car = initializer.makeCopCar();

    track.setCurrentState(straight);
    car->setSpeed(4);
    music.openFromFile(musicFilePath);
    music.setLoop(true);
    music.setVolume(10);
    music.play();




    //initialization of game items
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

    SpeedLines speed1 = initializer.makeSpeed1Lines();
    SpeedLines speed2 = initializer.makeSpeed2Lines();
    SpeedLines speed3 = initializer.makeSpeed3Lines();

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
    speedLinesHandler.add(&speed3);

    


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



    sf::View fixedView(sf::FloatRect(0,0,xRes, yRes));
    sf::View gameView;

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
            distance += car->getSpeed() / 3;
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
        if (car->getSpeed() > 2) {
            speed1.setOn();
        }
        else speed1.setOff();
        if (car->getSpeed() > 4) {
            speed2.setOn();
        }
        else speed2.setOff();
        if (car->getSpeed() > 5) {
            speed3.setOn();
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
        roadTransitionsHandler.draw(window);
        horizonLine.draw(window);
        car->draw(window);


        //adjust view based on car movement
        updateView(window, car->getSprite().getPosition().x + (yRes * .2), xRes * 0.2);


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
    system("cls");
    std::cout << lapTimeText.getString().toAnsiString() << timePenaltyText.getString().toAnsiString();


    return 0;
}