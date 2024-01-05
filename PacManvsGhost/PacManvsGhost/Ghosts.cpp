#include "Ghosts.h"


Ghosts::Ghosts()
{
	//setting ghosts variables - Creates a red rectangle
	ghosts.setFillColor(sf::Color::Red);
	ghosts.setSize(sf::Vector2f(25, 25));
	ghosts.setPosition(1000, 10);

}

void Ghosts::update(sf::TcpSocket& socket, float dt)
{
	// Sets a new position for the ghost using the data it receives and manipulates from the Networking class
	ghosts.setPosition(ghostLP.position);
}


sf::RectangleShape& Ghosts::getGhost()
{
	// Gets the ghost
	return ghosts;
}

GhostPredictionVar& Ghosts::getState()
{
	// Gets the struct variable 
	return ghostLP;
}

void Ghosts::setState(GhostPredictionVar& newState)
{
	// Updates the Struct - This will hold the ghosts position
	ghostLP = newState;
}