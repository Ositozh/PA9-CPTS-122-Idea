#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>



void singlePlayer(sf::RenderWindow& window);

void controlCar(sf::Sprite& car, int& gear);

void applyTimePenalty(int& outOfBoundsCount, sf::Time& timePenalty);

void updateLapTimer(std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime);

void displayLapTime(sf::RenderWindow& window, std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime, sf::Font& font, sf::Text& lapTimeText);

