#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "PacMan.h"
#include "Ghosts.h"
#include "Balls.h"

class Networking
{

	// This class handles all of the data that the Ghost will need to send and receive to the server.

public:

	//Constructor and Deconstructor
	Networking();
	~Networking();

	// Network update - Will update all of the data that this client will receive from the server and send to the server
	void update(sf::TcpSocket& socket, float dt, Ghosts& ghosts, PacMan& pm, Balls& balls);

	void ReceivePositionPacket(sf::Packet& receivedPacket, float dt, PacMan& pm);			// Receives Position of other player
	void ReceiveBallPacket(sf::Packet& receivedPacket, float dt, Balls& balls);				// Receives Ball positions from Server
	void ReceiveTimePacket();																// Receives the Start Timer packet from Server

	void SendPostionPacket(sf::Packet& receivedPacket, Ghosts& ghosts);						// Send Players Position to server

	float getGameTimer();																	// Getter function that gets the current Time
	float lerp(float sv, float ev, float pct);												// Lerp Function - Linear Interpolation

	// Timer variables
	float delayTimer = 0.1f;			// Cooldown Time
	sf::Clock clientTimer;				// Clock 
	float time;							// This is the in game timer sent from the Server

	// Linear Prediction 
	float predictionInterval = 0.01;
	bool isFirstPacket;					// makes sure we dont apply prediction to the first packet
	float previousX;					// Will store the previous packets position
	float previousY;

	// Ball Variables
	vector <sf::Vector2f> ballPositions;
	int ballIDIncrement;
};

// Enum Variables for each type of packet that could be received - Int8s to send less data to server
enum packetIDs : sf::Int8
{

	PT_POSITIONS = 2,
	PT_START = 3,
	PT_BALLS
};


