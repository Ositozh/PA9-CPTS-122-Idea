#pragma once
using std::cout;
using std::endl;

#include "functions.hpp"


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

    // Define gear
    int gear = 1;

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

        // Control the car
        controlCar(car, gear);

        // Check for out of bounds
        if (car.getPosition().x < 0 || car.getPosition().x > 800) 
        
        {
            cout << "Warning: Out of bounds!" << endl;
            outOfBoundsCount++;
            applyTimePenalty(outOfBoundsCount, timePenalty);
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

void controlCar(sf::Sprite& car, int& gear) {
    float speed = 5.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        car.move(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        car.move(speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (gear > 1) {
            gear--;
            std::cout << "Shifted down to gear " << gear << std::endl;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (gear < 7) {
            gear++;
            std::cout << "Shifted up to gear " << gear << std::endl;
        }
    }
}

void applyTimePenalty(int& outOfBoundsCount, sf::Time& timePenalty) 

{
    if (outOfBoundsCount >= 3) {
        std::cout << "Time penalty applied!" << std::endl;
        timePenalty += sf::seconds(5);
    }
}

void updateLapTimer(std::chrono::steady_clock::time_point& lapStartTime, std::chrono::steady_clock::time_point& lapEndTime) 

{
    lapEndTime = std::chrono::steady_clock::now();
}

void displayLapTime(sf::RenderWindow& window, std::chrono::steady_clock::time_point& lapStartTime, 
    std::chrono::steady_clock::time_point& lapEndTime, sf::Font& font, sf::Text& lapTimeText)

{auto lapDuration = std::chrono::duration_cast<std::chrono::milliseconds>(lapEndTime - lapStartTime);
    std::string lapTimeString = "Lap Time: " + std::to_string(lapDuration.count() / 1000) + "s";
    lapTimeText.setString(lapTimeString);
    window.draw(lapTimeText);
}

