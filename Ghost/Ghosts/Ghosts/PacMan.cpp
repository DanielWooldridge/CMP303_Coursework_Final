#include "PacMan.h"

// Constructor
PacMan::PacMan()
{
	// Setting Pacman variables - Builds what we see
	pm.setRadius(25);
	pm.setFillColor(sf::Color::Yellow);
	pm.setPosition(10, 10);
	setCollisionBox(0, 0, 40, 40);
}

// PacMan update
void PacMan::update(sf::TcpSocket& socket, float dt)
{
	// Sets a new position for pacman using the data it receives and manipulates from the Networking class
	pm.setPosition(pacLP.position);
}

// PacMan Getter
sf::CircleShape& PacMan::getPacMan()
{
	// Gets the ghost
	return pm;
}

PacPredictionVar& PacMan::getState()
{
	// Gets the struct variable 
	return pacLP;
}

void PacMan::setState(PacPredictionVar& newState)
{
	// Updates the Struct - This will hold the ghosts position
	pacLP = newState;
}


