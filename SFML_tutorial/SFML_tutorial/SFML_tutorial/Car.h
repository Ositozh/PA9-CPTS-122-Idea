#pragma once
#include "pa9.hpp"

const int maxTurn = 2;

class Car {
protected:
    float speed;
    float direction;
    float acceleration;
    float turningSpeed;

    float timePassed;

    float yRes;

    sf::Sprite carSprite;
public:
    Car() : speed(0), direction(0), acceleration(0), turningSpeed(0), timePassed(0), yRes(0){}

    virtual ~Car() {}

    virtual float getSpeed() const = 0;
    virtual void setSpeed(float speed) = 0;

    virtual float getDirection() const = 0;
    virtual void setDirection(float direction) = 0;

    virtual float getAcceleration() const = 0;
    virtual void setAcceleration(float acceleration) = 0;

    virtual float getTurningSpeed() const = 0;
    virtual void setTurningSpeed(float turningSpeed) = 0;

    virtual void setYRes(const float yResolution) {
        yRes = yResolution;
    }

    virtual sf::Sprite& getSprite() {
        return carSprite;
    }
    virtual void setSprite(sf::Sprite& sprite) {
        carSprite = sprite;
    }

    virtual void draw(sf::RenderWindow& window) {
        window.draw(carSprite);
    }


    // Method to update the car's state, to be defined by derived classes
    virtual void update(sf::Keyboard::Key key, float deltaTime) = 0;
};
