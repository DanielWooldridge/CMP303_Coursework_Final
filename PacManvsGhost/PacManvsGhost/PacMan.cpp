#include "PacMan.h"
#include "Balls.h"  


PacMan::PacMan()
{
	//setting Pacman variables
	pm.setRadius(25);
	pm.setFillColor(sf::Color::Yellow);
	pm.setPosition(10, 10);
}


sf::CircleShape& PacMan::getPacMan()
{
	return pm;
}

void PacMan::handleInput(float dt)
{

	//move left
	if (input->isKeyDown(sf::Keyboard::Left)) {

		pm.move(sf::Vector2f(-speed * dt, 0.0f));
	}
	//move right 
	else if (input->isKeyDown(sf::Keyboard::Right)) {

		pm.move(sf::Vector2f(speed * dt, 0.0f));
	}
	//move down 
	else if (input->isKeyDown(sf::Keyboard::Down)) {

		pm.move(sf::Vector2f(0.0f, speed * dt));
	}
	//move up
	else if (input->isKeyDown(sf::Keyboard::Up)) {

		pm.move(sf::Vector2f(0.0f, -speed * dt));
	}

}

void PacMan::update(sf::TcpSocket& socket, float dt)
{

}



