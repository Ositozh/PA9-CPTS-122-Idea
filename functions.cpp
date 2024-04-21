#include <iostream>
#include "functions.hpp"

void printMenu() 

{
    std::cout << "===== Racing Game Menu =====" << std::endl;
    std::cout << "1. Single Player" << std::endl;
    std::cout << "2. Double Player" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) 
    
    {
    case 1:
        std::cout << "You chose Single Player mode" << std::endl;
        //theres gonna be code here
        break;
    case 2:
        std::cout << "You chose Double Player mode" << std::endl;
        //theres gonna be code here

        break;
    case 3:
        std::cout << "Exiting the game" << std::endl;
        break;
    default:
        std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
        break;
    }
}

void singlePlayer(sf::RenderWindow& window)

{
    std::cout << "Single Player mode" << std::endl;
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("car.png")) 
    
    {
        std::cerr << "Failed to load car texture!" << std::endl;
        return;
    }
    sf::Sprite car(carTexture);
    car.setPosition(400, 500); // Initial position of the car

    // Define gear
    int gear = 1;

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

        // Handle keyboard inputs
        controlCar(car, gear);

        // Clear the window
        window.clear();

        // Draw the car
        window.draw(car);

        // Display the window contents
        window.display();
    }
}

void doublePlayer(sf::RenderWindow& window)

{
    std::cout << "Double Player mode" << std::endl;
    sf::Texture carTexture;
    if (!carTexture.loadFromFile("car.png")) {
        std::cerr << "Failed to load car texture!" << std::endl;
        return;
    }
    sf::Sprite car1(carTexture);
    sf::Sprite car2(carTexture);
    car1.setPosition(200, 500); // Initial position of player 1's car
    car2.setPosition(600, 500); // Initial position of player 2's car

    // Define gear for each player
    int gear1 = 1;
    int gear2 = 1;

    // Game loop
    bool player1Turn = true; // Flag to track whose turn it is
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            
            {
                window.close();
            }
        }

        // Handle keyboard inputs for player 1 if it's their turn
        if (player1Turn) {
            controlCar(car1, gear1);
        }
        // Handle keyboard inputs for player 2 if it's their turn
        else {
            controlCar(car2, gear2);
        }

        // Toggle player turn for the next iteration
        player1Turn = !player1Turn;

        // Clear the window
        window.clear();

        // Draw the cars for player 1 and player 2
        window.draw(car1);
        window.draw(car2);

        // Display the window 
        window.display();
    }
}

void gameLoop(int option, sf::RenderWindow& window)

{
    if (option == 1) 
    {
        singlePlayer(window);
    }
    else if (option == 2) 
    {
        doublePlayer(window);
    }
    else if (option == 3) 
    {
        std::cout << "Exiting the game" << std::endl;
    }
    else {
        std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
    }
}



void controlCar(sf::Sprite& car, int& gear) 

{
    // Define movement speed
    float speed = 10.0f;

    // Handle keyboard inputs
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
    
    {
        car.move(-speed, 0); // Move left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
    
    {
        car.move(speed, 0); // Move right
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
    
    {
        // Shift down if not already in the lowest gear
        if (gear > 1) 
        
        {
            gear--;
            std::cout << "Shifted down to gear " << gear << std::endl;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
    
    {
        // Shift up if not already in the highest gear
        if (gear < 7) 
        
        {
            gear++;
            std::cout << "Shifted up to gear " << gear << std::endl;
        }
    }
}
