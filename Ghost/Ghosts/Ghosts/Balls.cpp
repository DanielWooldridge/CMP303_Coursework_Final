#include "Balls.h"  

Balls::Balls()
{
}

// Function to create balls
void Balls::createBalls(sf::Vector2f positions, int ID)
{
    // Create a new circle shape
    sf::CircleShape ball;

    // Set ball with basic features - position sent from networking class, received from server
    ball.setRadius(5);
    ball.setFillColor(sf::Color::White);
    ball.setPosition(positions);

    // Set ID and add it to the Vector
    int ballID = ID;
    ballIDs.push_back(ballID);

    // Add ball to Vector
    balls.push_back(ball);
}

// Function to render balls
void Balls::render(sf::RenderWindow& window)
{
    // Run through the vectore holding the balls and draw
    for (const auto& ball : balls) {
        window.draw(ball);
    }
}

