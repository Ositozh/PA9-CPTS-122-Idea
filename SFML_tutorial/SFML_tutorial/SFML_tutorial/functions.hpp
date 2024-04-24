#pragma once
#include "pa9.hpp"
#include "InitializerHelper.hpp"



void applyTimePenalty(int& outOfBoundsCount, sf::Time& timePenalty);

void updateLapTimer(std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime);

void displayLapTime(sf::RenderWindow& window, std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime, sf::Font& font, sf::Text& lapTimeText);

void displayPenaltyTime(sf::RenderWindow& window, sf::Time& timePenalty, sf::Font& font, sf::Text& penaltyTimeText);

void updateView(sf::RenderWindow& window, const float xCoord, const float deadZoneSize);

bool consoleMenu(int& trackChoice, int& carChoice);