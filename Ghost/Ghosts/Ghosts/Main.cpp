// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "SFML/Network.hpp"
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "level.h"


int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 675), "CMP303_Coursework");

	// Initialise input and level objects.
	AudioManager audioManager;
	Input input;
	GameState gameState;
	sf::TcpSocket socket;
	float sTime;
	Level level(&window, &socket, &sTime, &input);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Game Loop
	while (window.isOpen())
	{
		//Process window events
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setLeftMouse(Input::MouseState::DOWN);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setRightMouse(Input::MouseState::DOWN);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setLeftMouse(Input::MouseState::UP);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setRightMouse(Input::MouseState::UP);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		// Call standard game loop functions (input, update and render)
		level.handleInput(deltaTime);
		level.update(socket, deltaTime);
		level.render();

		// Update input class, handle pressed keys
		// Must be done last.
		input.update();
	}

}

