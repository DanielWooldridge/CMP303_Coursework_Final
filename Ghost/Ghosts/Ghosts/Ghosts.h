#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Framework/Input.h"
#include <SFML/Network.hpp>
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Input.h"

using namespace std;
class Ghosts : GameObject
{
public:
	//Constructor and Deconstructor
	Ghosts();

	//Base functions
	sf::RectangleShape getGhosts();					// Getter Function
	void handleInput(float dt);						// User Input
	void update(sf::TcpSocket& socket, float dt);   // update function


	//Ghosts
	sf::RectangleShape ghosts;
	//Pacman
	sf::CircleShape pm;
	//Input
	Input* input;




protected:

	//ghost player Stats
	float speed = 250.0f;

};

