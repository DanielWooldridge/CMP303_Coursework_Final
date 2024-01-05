#include "Networking.h"

Networking::Networking()
{

	// Set variables values
	time = 0.0f;
	ballIDIncrement = 0;
	isFirstPacket = true;	// Flag used to make sure we dont apply prediction to the first packet
	previousX = 0.0f;
	previousY = 0.0f;
}

Networking::~Networking()
{

}

void Networking::update(sf::TcpSocket& socket, float dt, Ghosts& ghosts, PacMan& pm, Balls& balls)
{
	// Get both pacman and ghost
	pm.getPacMan();
	ghosts.getGhost();

	/* If timer is bigger than 0.05 run this if statement - this code will receive the data for PacMans position and will also send the Ghosts position and more,
		we do this with an interval so that we don't overload the system with data. If the system does overload it will cause the programs to freeze. */


	if (delayTimer > 0.01)
	{
		
		// Sending Players position //
		sf::Packet packet;
		
		SendPositionPacket(packet, pm);

		if (socket.send(packet) != sf::Socket::Done)
		{
			std::cout << "Error" << std::endl;
		}
		packet.clear();


		// Receiving Packets - Time, Player Position, Ball Position //
		sf::Packet receivedPacket;
		if (socket.receive(receivedPacket) == sf::Socket::Done)
		{
			// Get packet from Server
			sf::Int8 packetType;
			receivedPacket >> packetType;

			// Depending on which Type of Packet run the designated function
			if (packetType == PT_START) 
			{
				ReceiveTimePacket();								// Time 
			}
			else if (packetType == PT_POSITIONS) 
			{
				ReceivePositionPacket(receivedPacket, dt, ghosts);	// Player Position 
			}
			else if (packetType == PT_BALLS)
			{
				ReceiveBallPacket(receivedPacket, dt, balls);		// Ball Position
			}
		}

		// Set delay timer back to 0
		delayTimer = 0;
	}

	// Add delta Time to Timer
	delayTimer += dt;
}

// Time Packet
void Networking::ReceiveTimePacket()
{
	// Restarts a timer
	clientTimer.restart();

	// Calculate the elapsed time in seconds
	float clientElapsedSeconds = clientTimer.getElapsedTime().asSeconds();

	// Update the client's time variable
	time = clientElapsedSeconds;


	//cout << "Client Timer Restarted. Current Time: " << time << " seconds" << endl;
}

// Player Position Packet
void Networking::ReceivePositionPacket(sf::Packet& receivedPacket, float dt, Ghosts& ghosts)
{

	cout << "Previous Position: " << previousX << ", " << previousY << endl;

	// Set new Variables to hold packets contents
	float x, y;
	receivedPacket >> x >> y;
	cout << "Received Position: " << x << ", " << y << endl;

	GhostPredictionVar& ghostPL = ghosts.getState(); // Get the current state of ghost (its position)

	
	/* Prediction and Interpolation
	 If this is the clients first packet received or the other player is not moving */

	if (isFirstPacket || (x == previousX && y == previousY))
	{
		// Dont use prediction - Lerp to the position of the raw position received from the server
		ghostPL.position.x = lerp(ghostPL.position.x, x, 100.0f * dt);
		ghostPL.position.y = lerp(ghostPL.position.y, y, 100.0f * dt);

		// Reset
		isFirstPacket = false;
	}

	// If the player is moving
	else
	{
		// calculate using the ghosts speed a predicted value on where it will move next
		float predXvalue = x + ghostPL.velocity.x * predictionInterval;
		float predYvalue = y + ghostPL.velocity.y * predictionInterval;
		std::cout << " Predicted position: " << predXvalue << ", " << predYvalue << endl;

		// Use linear interpolation to smooth out the movement this is between the received position and the predicted value we have calculated
		ghostPL.position.x = lerp(ghostPL.position.x, predXvalue, 100.0f * dt);
		ghostPL.position.y = lerp(ghostPL.position.y, predYvalue, 100.0f * dt);
		std::cout << " Interpolated position: " << ghostPL.position.x << ", " << ghostPL.position.y << endl;
	}

	// Save the current values of x and y for the next iteration
	previousX = x;
	previousY = y;

	ghosts.setState(ghostPL);

}

// Balls Position Packet
void Networking::ReceiveBallPacket(sf::Packet& receivedPacket, float dt, Balls& balls)
{
	// floats to hold packets contents
	float bx, by;
	receivedPacket >> bx >> by;

	// Create an ID for that ball
	int ballID = ballIDIncrement;
	
	// Create ball using position and ID
	balls.createBalls(sf::Vector2f(bx, by), ballID);
		
	std::cout << "Received ball position: " << bx << ", " << by << ", With ID: " << ballID << std::endl;

	ballIDIncrement++;
}

// Player Position
void Networking::SendPositionPacket(sf::Packet& packet, PacMan& pm)
{
	// Send with Position type enum variable the p[layers current position
	packet << PT_POSITIONS << pm.getPacMan().getPosition().x << pm.getPacMan().getPosition().y;
}

// Game Time
float Networking::getGameTimer()
{

	// Calculate the elapsed time from the client timer when needed
	float clientElapsedSeconds = clientTimer.getElapsedTime().asSeconds();

	//cout << "Client Timer Elapsed: " << clientElapsedSeconds << " seconds" << endl;

	return clientElapsedSeconds;

	
}

// Linear Interpolation
float Networking::lerp(float sv, float ev, float pct) {
	return (sv + (ev - sv) * pct);
}
