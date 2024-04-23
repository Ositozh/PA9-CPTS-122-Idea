#pragma once
#include "Car.h"
#include "pa9.hpp"

class SportsCar : public Car
{

public:
    SportsCar();

    float getSpeed() const override;
    void setSpeed(float sp) override;

    float getDirection() const override;
    void setDirection(float dir) override;

    float getAcceleration() const override;
    void setAcceleration(float accel) override;

    float getTurningSpeed() const override;
    void setTurningSpeed(float turnSpeed) override;

    void update(sf::Keyboard::Key key, float deltaTime) override;
};


class SafetyCar : public Car
{
public:
    SafetyCar();

    float getSpeed() const override;
    void setSpeed(float sp) override;

    float getDirection() const override;
    void setDirection(float dir) override;

    float getAcceleration() const override;
    void setAcceleration(float accel) override;

    float getTurningSpeed() const override;
    void setTurningSpeed(float turnSpeed) override;

    void update(sf::Keyboard::Key key, float deltaTime) override;
};





class CopCar : public Car
{
public:
    CopCar();

    float getSpeed() const override;
    void setSpeed(float sp) override;

    float getDirection() const override;
    void setDirection(float dir) override;

    float getAcceleration() const override;
    void setAcceleration(float accel) override;

    float getTurningSpeed() const override;
    void setTurningSpeed(float turnSpeed) override;

    void update(sf::Keyboard::Key key, float deltaTime) override;
};

