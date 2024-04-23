#include "CarTypes.h"

// SportsCar 
SportsCar::SportsCar() : Car() {
    acceleration = 0.3;     // high acceleration
    turningSpeed = 45;      // moderate turning speed
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
void SportsCar::update(sf::Keyboard::Key key) {
    //where the movement code where go
}

// Truck 
Truck::Truck() : Car() {
    acceleration = 0.1;     // Lower acceleration
    turningSpeed = 60;      // Higher turning speed

    //Lower accereration but should be easier to control
}

//same methods as in SportsCar, but with Trucks specifics
float Truck::getSpeed() const { return speed; }
void Truck::setSpeed(float sp) { speed += sp * acceleration; }
float Truck::getDirection() const { return direction; }
void Truck::setDirection(float dir) { direction = dir; }
float Truck::getAcceleration() const { return acceleration; }
void Truck::setAcceleration(float accel) { acceleration = accel; }
float Truck::getTurningSpeed() const { return turningSpeed; }
void Truck::setTurningSpeed(float turnSpeed) { turningSpeed = turnSpeed; }
void Truck::update(sf::Keyboard::Key key) {
    //where the movement code where go
}

// FormulaCar 
FormulaCar::FormulaCar() : Car() 
{
    acceleration = 0.5;     // Very high acceleration
    turningSpeed = 15;      // Lower turning speed

    //very fast car but harder to control
}

//same methods as in SportsCar, but with FormulaCars specifics
float FormulaCar::getSpeed() const { return speed; }
void FormulaCar::setSpeed(float sp) { speed += sp * acceleration; }
float FormulaCar::getDirection() const { return direction; }
void FormulaCar::setDirection(float dir) { direction = dir; }
float FormulaCar::getAcceleration() const { return acceleration; }
void FormulaCar::setAcceleration(float accel) { acceleration = accel; }
float FormulaCar::getTurningSpeed() const { return turningSpeed; }
void FormulaCar::setTurningSpeed(float turnSpeed) { turningSpeed = turnSpeed; }
void FormulaCar::update(sf::Keyboard::Key key) {
    //where the movement code where go
}
