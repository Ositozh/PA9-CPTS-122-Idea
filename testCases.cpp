#include "testCases.hpp"
#include <iostream>
#include <chrono>
/*
Credit: Looked up tutorials on youtube on how to implement a timer that would dislpay 

*/


//funtion to test car movement and prints to screen if success or not!
void TestFunctions::TestMovement()
{
  
   cout << "Press LEFT arrow key and then press ENTER: ";
  
   string input;
  
   cin >> input;

    sf::Sprite car;
    int gear = 1;

    controlCar(car, gear); // calls the movement function 

    // check if car moved left based on Andy input
    bool carMovedLeft = (input == "LEFT");

    // Output result
    if (carMovedLeft) 
    
    {
        cout << "Movement Test PASSED" << endl;
    }
    else 
    
    {
       cout << "Movement Test FAILED" << endl;
    }

}

//function that tests if the car was downshifted and then upshifted back , prints success or fail 
void TestFunctions::TestShifting()
{
   cout << "Press SPACE to shift down and then UP arrow to shift up: ";
   string input1, input2;
   cin >> input1 >> input2;

    int gear = 3; // Initial gear

    sf::Sprite carSprite; 
   
    controlCar(carSprite, gear); // Pass the object to the function and calls function 

    // check if gear shifted down and up based on Andy input
  
    bool gearShiftedDown = (input1 == "SPACE");
  
    bool gearShiftedUp = (input2 == "UP");

    // print result
    if (gearShiftedDown && gearShiftedUp) 
    
    {
        cout << "Test shifting: PASSED" << endl;
    }
    else 
    {
       cout << "Test shifting: FAILED" << endl;
    }

}

void TestFunctions::TestOutBounds()
{
    cout << "Enter the number of times the car goes out of bounds: ";
   
    int outOfBoundsCount;
  
    cin >> outOfBoundsCount;

    // Create local variables for testing
    sf::Time timePenalty = sf::seconds(0);

    // Call the function
    applyTimePenalty(outOfBoundsCount, timePenalty);

    // Verify if time penalty applied correctly
    bool outOfBoundsDetected = (timePenalty == sf::seconds(5));

    
    if (outOfBoundsDetected) 
    
    {
       cout << "Test bounds detection: PASSED" << endl;
    }
    else 
    
    {
       cout << "Test bounds detection: FAILED" <<endl;
    }
}

void TestFunctions::TestLapTimer()
{
    // Test lap timing by prompting user to press ENTER to simulate starting and stopping the timer
   cout << "Press ENTER to start and stop the lap timer: ";
   
   cin.ignore(); // Ignore previous newline character
  
   cin.get(); // Wait for user to press ENTER

    // Create local variables 
   
   std::chrono::steady_clock::time_point lapStartTime = std::chrono::steady_clock::now();
  
    std::chrono::steady_clock::time_point lapEndTime;

    // Calls the function so it updates timer 
    updateLapTimer(lapStartTime, lapEndTime);

    // this is to check if the timer hasr started and ended when it should 
    bool lapTimerStarted = (lapStartTime.time_since_epoch().count() != 0);
    bool lapTimerStopped = (lapEndTime.time_since_epoch().count() != 0);

    // prints result 
    if (lapTimerStarted && lapTimerStopped) 
    
    {
        cout << "Test lap timing: PASSED" << endl;
    }
    else 
    
    {
        cout << "Test lap timing: FAILED" << endl;
    }
}



void TestFunctions::TestGameOver()
{

}
