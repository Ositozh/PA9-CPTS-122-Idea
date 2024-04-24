#include "CarTypes.h"

// SportsCar 
SportsCar::SportsCar() : Car() { //max speed 5
    acceleration = 0.3;     // high acceleration
    turningSpeed = 3.2;      // moderate turning speed

    //balanced car
}

float SportsCar::getSpeed() const { return speed; }
void SportsCar::setSpeed(float sp) { speed += sp * acceleration; }
float SportsCar::getDirection() const { return direction; }
void SportsCar::setDirection(float dir) { direction = dir; }
float SportsCar::getAcceleration() const { return acceleration; }
void SportsCar::setAcceleration(float accel) { acceleration = accel; }
float SportsCar::getTurningSpeed() const { return turningSpeed; }
void SportsCar::setTurningSpeed(float turnSpeed) { turningSpeed = turnSpeed; }
void SportsCar::update(sf::Keyboard::Key key, float deltaTime) {
    timePassed += deltaTime;
    sf::IntRect spriteLocation;
    switch (key) {
    case (sf::Keyboard::Up):
        if (speed < 5 && timePassed > 0.4) {
            setSpeed(0.025);
            timePassed -= deltaTime;
        }
        break;
    case (sf::Keyboard::Left):
        if (getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
            if (direction > -1 * maxTurn && timePassed > 0.3) {
                direction -= 1;
                if (direction > -1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction <= -1 * maxTurn) {
                    spriteLocation.left = 36;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 120;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(-turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Right):
        if (getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
            if (direction < maxTurn && timePassed > 0.3) {
                direction += 1;
                if (direction < 1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction >= maxTurn) {
                    spriteLocation.left = 360;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 280;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Down):
        if (speed > 1 && timePassed > 0.4) {
            setSpeed(-0.02);
            timePassed -= deltaTime;
        }
    }
}

// SafetyCar 
SafetyCar::SafetyCar() : Car() {
    acceleration = 0.1;     // Lower acceleration
    turningSpeed = 5;      // Higher turning speed

    //Lower accereration but should be easier to control
}

//same methods as in SportsCar, but with SafetyCars specifics
float SafetyCar::getSpeed() const { return speed; }
void SafetyCar::setSpeed(float sp) { speed += sp * acceleration; }
float SafetyCar::getDirection() const { return direction; }
void SafetyCar::setDirection(float dir) { direction = dir; }
float SafetyCar::getAcceleration() const { return acceleration; }
void SafetyCar::setAcceleration(float accel) { acceleration = accel; }
float SafetyCar::getTurningSpeed() const { return turningSpeed; }
void SafetyCar::setTurningSpeed(float turnSpeed) { turningSpeed = turnSpeed; }
void SafetyCar::update(sf::Keyboard::Key key, float deltaTime) {
    timePassed += deltaTime;
    sf::IntRect spriteLocation;
    switch (key) {
    case (sf::Keyboard::Up):
        if (speed < 4.2 && timePassed > 0.4) {
            setSpeed(0.025);
            timePassed -= deltaTime;
        }
        break;
    case (sf::Keyboard::Left):
        if (getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
            if (direction > -1 * maxTurn && timePassed > 0.3) {
                direction -= 1;
                if (direction > -1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction <= -1 * maxTurn) {
                    spriteLocation.left = 36;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 120;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(-turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Right):
        if (getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
            if (direction < maxTurn && timePassed > 0.3) {
                direction += 1;
                if (direction < 1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction >= maxTurn) {
                    spriteLocation.left = 360;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 280;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Down):
        if (speed > 1 && timePassed > 0.4) {
            setSpeed(-0.02);
            timePassed -= deltaTime;
        }
    }
}

// CopCar 
CopCar::CopCar() : Car()
{
    acceleration = 0.5;     // Very high acceleration
    turningSpeed = 2.8;      // Lower turning speed

    //very fast car but harder to control
}

//same methods as in SportsCar, but with CopCars specifics
float CopCar::getSpeed() const { return speed; }
void CopCar::setSpeed(float sp) { speed += sp * acceleration; }
float CopCar::getDirection() const { return direction; }
void CopCar::setDirection(float dir) { direction = dir; }
float CopCar::getAcceleration() const { return acceleration; }
void CopCar::setAcceleration(float accel) { acceleration = accel; }
float CopCar::getTurningSpeed() const { return turningSpeed; }
void CopCar::setTurningSpeed(float turnSpeed) { turningSpeed = turnSpeed; }
void CopCar::update(sf::Keyboard::Key key, float deltaTime) {
    timePassed += deltaTime;
    sf::IntRect spriteLocation;
    switch (key) {
    case (sf::Keyboard::Up):
        if (speed < 6.5 && timePassed > 0.4) {
            setSpeed(0.025);
            timePassed -= deltaTime;
        }
        break;
    case (sf::Keyboard::Left):
        if (getSprite().getPosition().x > -.2 * 16 / 9 * yRes) {
            if (direction > -1 * maxTurn && timePassed > 0.3) {
                direction -= 1;
                if (direction > -1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction <= -1 * maxTurn) {
                    spriteLocation.left = 36;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 120;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(-turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Right):
        if (getSprite().getPosition().x < 1.2 * 16 / 9 * yRes - .4 * yRes) {
            if (direction < maxTurn && timePassed > 0.3) {
                direction += 1;
                if (direction < 1) {
                    spriteLocation.left = 200;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                else if (direction >= maxTurn) {
                    spriteLocation.left = 360;
                    spriteLocation.top = 296;
                    spriteLocation.width = 44;
                    spriteLocation.height = 40;
                }
                else {
                    spriteLocation.left = 280;
                    spriteLocation.top = 296;
                    spriteLocation.width = 40;
                    spriteLocation.height = 40;
                }
                carSprite.setTextureRect(spriteLocation);
                timePassed = 0;
            }
            carSprite.move(turningSpeed * .001 * yRes, 0);
        }
        break;
    case (sf::Keyboard::Down):
        if (speed > 1 && timePassed > 0.4) {
            setSpeed(-0.02);
            timePassed -= deltaTime;
        }
    }
}
