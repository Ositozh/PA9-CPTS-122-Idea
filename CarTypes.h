#pragma once
#include "Car.h"


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

    void update(sf::Keyboard::Key key) override;
};


class Truck : public Car
{
public:
    Truck();

    float getSpeed() const override;
    void setSpeed(float sp) override;

    float getDirection() const override;
    void setDirection(float dir) override;

    float getAcceleration() const override;
    void setAcceleration(float accel) override;

    float getTurningSpeed() const override;
    void setTurningSpeed(float turnSpeed) override;

    void update(sf::Keyboard::Key key) override;
};





class FormulaCar : public Car
{
public:
    FormulaCar();

    float getSpeed() const override;
    void setSpeed(float sp) override;

    float getDirection() const override;
    void setDirection(float dir) override;

    float getAcceleration() const override;
    void setAcceleration(float accel) override;

    float getTurningSpeed() const override;
    void setTurningSpeed(float turnSpeed) override;

    void update(sf::Keyboard::Key key) override;
};
