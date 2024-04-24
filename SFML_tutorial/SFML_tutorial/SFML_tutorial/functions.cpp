#include "functions.hpp"
using std::cout;
using std::endl;



void applyTimePenalty(int& outOfBoundsCount, sf::Time& timePenalty)

{
    if (outOfBoundsCount >= 3) {
        timePenalty += sf::seconds(3);
        outOfBoundsCount = 0;
    }
    else outOfBoundsCount++;
}

void updateLapTimer(std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime)

{
    lapEndTime = std::chrono::steady_clock::now();
}

void displayLapTime(sf::RenderWindow& window, std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime, sf::Font& font, sf::Text& lapTimeText)

{
    auto lapDuration = std::chrono::duration_cast<std::chrono::milliseconds>(lapEndTime - lapStartTime);
    std::string lapTimeString = "Lap Time: " + std::to_string(lapDuration.count() / 1000) + "s";
    lapTimeText.setString(lapTimeString);
    window.draw(lapTimeText);
}

void displayPenaltyTime(sf::RenderWindow& window, sf::Time& timePenalty, sf::Font& font, sf::Text& timePenaltyText)

{
    std::string timePenaltyString = "Penalty: " + std::to_string(timePenalty.asSeconds()) + "s";
    timePenaltyText.setString(timePenaltyString);
    window.draw(timePenaltyText);
}

void updateView(sf::RenderWindow& window, const float xCoord, const float deadZoneSize) 

{
    float viewCenter = window.getView().getCenter().x;
    sf::View view = window.getView();
    if (xCoord < viewCenter - deadZoneSize) {
        view.setCenter(view.getCenter().x - ((view.getCenter().x  - deadZoneSize) - xCoord), view.getCenter().y);
    }
    if (xCoord > viewCenter + deadZoneSize) {
        view.setCenter(view.getCenter().x + xCoord - view.getCenter().x - deadZoneSize, view.getCenter().y);
    }
    window.setView(view);
}

bool consoleMenu(int& trackChoice, int& carChoice)

{
    int choice;
    std::cout << "1: Play\n2: View Leaderboard\n3: Exit\n\n> ";
    std::cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        std::cout << "1: Track 1\n2: Track 2\n\n> ";
        std::cin >> trackChoice;
        system("cls");
        std::cout << "1: Sports Car (balanced)\n2: Safety Car (controllable)\n3: Cop Car (fast)\n\n> ";
        std::cin >> carChoice;
        break;
    case 2:
        //leaderboard viewing code
        break;
    case 3:
        return false;
    }
    return true;
}