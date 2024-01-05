#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "Framework/Input.h"



using namespace std;

// Struct Created to hold the players postiion and velocity - is used to call for prediction and interpolation
struct GhostPredictionVar
{
	sf::Vector2f position;
	sf::Vector2f velocity = (sf::Vector2f(250.f, 250.f));
};


class Ghosts : public GameObject
{
public:

	Ghosts();

	// Functions for Ghost
	void update(sf::TcpSocket& socket, float dt); // update function
	sf::RectangleShape& getGhost(); // Getter function


	// Ghost Variable
	sf::RectangleShape ghosts; 
	
	// Prediction Functions/Variables
	GhostPredictionVar& getState();	// State Getter
	void setState(GhostPredictionVar& newState); // State Setter
	

private:

	// Struct variable
	GhostPredictionVar ghostLP;

};



