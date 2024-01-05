#include "Ghosts.h"
#include "Framework/GameObject.h"
Ghosts::Ghosts()
{

	//setting ghosts variables
	ghosts.setFillColor(sf::Color::Red);
	ghosts.setSize(sf::Vector2f(25, 25));
	ghosts.setPosition(1000, 10);

}


sf::RectangleShape Ghosts::getGhosts()
{
	return ghosts;
}

void Ghosts::handleInput(float dt)
{

	if (input->isKeyDown(sf::Keyboard::A)) {

		ghosts.move(-speed * dt, 0);

	}
	//move right 
	else if (input->isKeyDown(sf::Keyboard::D)) {

		ghosts.move(speed * dt, 0);
	}
	//move down 
	else if (input->isKeyDown(sf::Keyboard::S)) {

		ghosts.move(0, speed * dt);
	}
	//move up
	else if (input->isKeyDown(sf::Keyboard::W)) {

		ghosts.move(0, -speed * dt);
	}

}

void Ghosts::update(sf::TcpSocket& socket, float dt)
{

}

