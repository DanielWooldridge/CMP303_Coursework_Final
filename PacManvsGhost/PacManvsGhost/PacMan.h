#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Collision.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <sstream>
#include "Framework/Input.h"
#include "Ghosts.h"
#include "Balls.h"

// Forward declaration of Balls class
class Balls;

using namespace std;
class PacMan :
	public GameObject
{
public:

	// Constructor and Deconstructor
	PacMan();

	// Base functions
	sf::CircleShape& getPacMan(); // Getter function
	void handleInput(float dt); //User Input
	void update(sf::TcpSocket& socket, float dt); //update function


	// PacMan
	sf::CircleShape pm;
	Input* input; // input used to make pacman move

	// Ghosts
	Ghosts ghosts;


protected:

	// PacMan player stats
	float speed = 250.0; // Speed 



};

