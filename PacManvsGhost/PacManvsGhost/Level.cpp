#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, sf::TcpSocket* socket, float* sTime, Input* input)
{

	window = hwnd;

	
	// CONNECTING TO THE SERVER //

	// Set a flag to see if we have connected to false
	correctIP = false;

	//Getting IP Address through user input
	string ip;

	while (!correctIP) {

		// Ask user for IP address
		std::cout << "IP Address (or type 'exit' to quit): ";
		std::cin >> ip;

		// User can exit if typed
		if (ip == "exit") {
			std::cout << "Exiting the program. Goodbye!" << std::endl;
			return;
		}

		// Sets a new IpAddress Variable to the users inputed answer
		sf::IpAddress serverIP(ip);

		// See if the IP Address exists
		if (serverIP == sf::IpAddress::None) {
			std::cout << "The IP Address you have entered is incorrect. Please try again." << std::endl; // Reject if not
		}
		else {
			std::cout << "Connected to IP Address: " << ip << "\n" << std::endl;

			// Let the user pick if this was the correct IP Address they wanted to connect too
			while (true) {
				std::cout << "Is this the correct address? (1 for yes, 0 for no): ";
				int choice;
				std::cin >> choice;

				if (choice == 1) {
					correctIP = true;
					std::cout << "You have confirmed the IP Address: " << ip << "\n" << std::endl;
					break;
				}
				else if (choice == 0) {
					std::cout << "Please enter the correct IP address." << std::endl;
					break;
				}
				else {
					std::cout << "Invalid choice. Please enter 1 to confirm or 0 to retry." << std::endl;
				}
			}
		}
	}

	//Getting Port Number through user input
	int portNum = 0;
	while (portNum != 2222) {

		cout << "Port Number: ";
		cin >> portNum;

		if (portNum != 2222)
		{
			cout << "The Port number you have entered is incorrect, Please try again \n";
		}
	}

	// Connect to the Server with these inputed answers
	sf::Socket::Status status = socket->connect(ip, portNum);

	if (status != sf::Socket::Done)
	{
		std::cout << "Failed to connect to the server" << std::endl;
	}
	else
	{
		std::cout << "Connected to the server!" << std::endl;
	}

	// Send the client ID to the server - Straight after it connects
	sf::Packet packet;
	std::string clientId = "PacMan";
	packet << clientId;
	socket->send(packet);
	packet.clear();

	pacman.input = input;

}

Level::~Level()
{

}

void Level::handleInput(float dt)
{

}

void Level::update(sf::TcpSocket& socket, float dt)
{
	// Call Functions needed for game to work
	ghosts.update(socket, dt);
	pacman.handleInput(dt);
	network.update(socket, dt, ghosts, pacman, balls);

	// Get the received time from the networking class 
	float receivedTime = network.getGameTimer();
	timeDisplay.renderTime(sf::seconds(receivedTime));
}

void Level::render()
{
	// Render Game 
	beginDraw();
	window->draw(pacman.getPacMan());
	window->draw(ghosts.getGhost());
	window->draw(header.renderHeader());
	window->draw(timeDisplay.renderTime(sf::seconds(network.getGameTimer())));
	balls.render(*window);
	endDraw();
}


// Begins rendering to the back buffer. Background colour set to black.
void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}

