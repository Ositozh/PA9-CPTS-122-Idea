#include "includes.hpp"

int main() {
    const float yRes = 1080;
    float xRes = 16.0 / 9 * yRes;
    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "PA9 Graphics");


    //Music Stuff
    /*
    sf::Music music;
    music.openFromFile("filepath");
    music.setLoop(true);
    music.play();
    */

    //Road Graphics
    sf::Color roadColor(220, 50, 50);

    Road straight; //for straight sections
    straight.addLine(0, .85 * yRes, .49 * xRes, .35 * yRes);
    straight.addLine(xRes, .85 * yRes, .51 * xRes, .35 * yRes);
    straight.setColor(roadColor);

    Road right; //for right turns
    sf::Vector2f p0(0, .95 * yRes); //start point of curve
    sf::Vector2f p1(.38 * xRes, .32 * yRes); //used to shape curve
    sf::Vector2f p2(.72 * xRes, .352 * yRes); //end point of curve
    right.addCurve(p0, p1, p2);
    p0 = sf::Vector2f(xRes, .8 * yRes);
    p1 = sf::Vector2f(.6 * xRes, .45 * yRes);
    p2 = sf::Vector2f(.76 * xRes, .342 * yRes);
    right.addCurve(p0, p1, p2);
    right.setColor(roadColor);

    Road left; //for left turns
    p0 = sf::Vector2f(xRes, .95 * yRes);
    p1 = sf::Vector2f(.62 * xRes, .32 * yRes);
    p2 = sf::Vector2f(.24 * xRes, .352 * yRes);
    left.addCurve(p0, p1, p2);
    p0 = sf::Vector2f(0, .8 * yRes);
    p1 = sf::Vector2f(.4 * xRes, .45 * yRes);
    p2 = sf::Vector2f(.24 * xRes, .342 * yRes);
    left.addCurve(p0, p1, p2);
    left.setColor(roadColor);



    //Horizon Graphics
    sf::Color horizonColor(160, 50, 200);

    GraphicsLayer horizonLine;
    horizonLine.addLine(0, 0.35 * yRes, xRes, 0.35 * yRes);
    horizonLine.setColor(horizonColor);

    GraphicsLayer background;
    background.addLine(0, 0.35 * yRes, 100, 0.25 * yRes);
    background.addLine(100, 0.25 * yRes, 100, 0.25 * yRes);
    background.setColor(sf::Color::White);


    bool displayStraight = true, displayLeft = false, displayRight = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    if (displayStraight) {
                        displayStraight = false;
                        displayLeft = true;
                    }
                    else if (displayLeft) {
                        displayLeft = false;
                        displayRight = true;
                    }
                    else {
                        straight.setColor(sf::Color::Cyan);
                        left.setColor(sf::Color::Cyan);
                        right.setColor(sf::Color::Cyan);
                        displayRight = false;
                        displayStraight = true;
                    }
                }
                    
                break;
            case sf::Event::MouseButtonPressed:
                // Handle mouse button press
                break;
                // Additional event types can be handled here
            }
        }
        if(displayStraight) straight.draw(window);
        if (displayLeft) left.draw(window);
        if (displayRight) right.draw(window);


        horizonLine.draw(window);
        //background.draw(window);
        window.display();
        window.clear();
    }     


    return 0;
}