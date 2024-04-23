#pragma once

using namespace std;

class Car {
protected:
    float speed;           
    float direction;       
    float acceleration;    
    float turningSpeed;    

public:
    Car() : speed(0), direction(0), acceleration(0), turningSpeed(0) {}

    virtual ~Car() {}

    virtual float getSpeed() const = 0;
    virtual void setSpeed(float speed) = 0;

    virtual float getDirection() const = 0;
    virtual void setDirection(float direction) = 0;

    virtual float getAcceleration() const = 0;
    virtual void setAcceleration(float acceleration) = 0;

    virtual float getTurningSpeed() const = 0;
    virtual void setTurningSpeed(float turningSpeed) = 0;

    // Method to update the car's state, to be defined by derived classes
    virtual void update(sf::Keyboard::Key key) = 0;
};
