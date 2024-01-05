#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "Framework/Input.h"

using namespace std;

// Struct Created to hold the players position and velocity - is used to call for prediction and interpolation
struct PacPredictionVar
{
    sf::Vector2f position;
    sf::Vector2f velocity = (sf::Vector2f(250.f, 250.f));
};

class PacMan :
    public GameObject
{

public:

    // Constructor
    PacMan();

    // PacMan Functions
    void update(sf::TcpSocket& socket, float dt); // Update Function
    sf::CircleShape& getPacMan();                 // getter Function

    // Pacman Variable
    sf::CircleShape pm;

    // Prediction Functions/Variables
    PacPredictionVar& getState();                   // State getter
    void setState(PacPredictionVar& newState);      // State Setter
   

private:

    // Struct variable
    PacPredictionVar pacLP;

};

