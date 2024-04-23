#include "functions.hpp"
using std::cout;
using std::endl;


void singlePlayer(sf::RenderWindow& window)

{
    cout << "Single Player mode" << endl;

    // Create car sprite
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("car.png"))
    {
        std::cerr << "Failed to load car texture!" << endl;
        return;
    }
    sf::Sprite car(carTexture);
    car.setPosition(400, 500); // Initial position of the car

    // Track out-of-bounds count and time penalty
    int outOfBoundsCount = 0;
    sf::Time timePenalty = sf::seconds(0);

    // Lap timer variables
    auto lapStartTime = std::chrono::steady_clock::now();
    auto lapEndTime = std::chrono::steady_clock::now();
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))

    {
        std::cerr << "Failed to load font!" << endl;
        return;
    }
    sf::Text lapTimeText;
    lapTimeText.setFont(font);
    lapTimeText.setCharacterSize(20);
    lapTimeText.setFillColor(sf::Color::White);
    lapTimeText.setPosition(600.f, 10.f);

    // Game loop
    while (window.isOpen())

    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))

        {
            if (event.type == sf::Event::Closed)

            {
                window.close();
            }
        }

        // Update lap timer
        updateLapTimer(lapStartTime, lapEndTime);

        // Clear the window
        window.clear();

        // Draw the car
        window.draw(car);

        // Display lap time
        displayLapTime(window, lapStartTime, lapEndTime, font, lapTimeText);

        // Display the window contents
        window.display();
    }
}

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