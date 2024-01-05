#pragma once
#include "Framework/Input.h"
#include <string>
#include <iostream>

#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include <string>
#include <iostream>
#include "Framework/TileMap.h"
#include "Framework/AudioManager.h"
#include "Framework/Collision.h"
#include "Framework/GameObject.h"
#include "Framework/GameState.h"

//new includes
#include "SFML/Network.hpp"
#include "Ghosts.h"
#include <SFML/Graphics.hpp>
#include "PacMan.h"
#include "Networking.h"
#include "UI.h"
#include "Balls.h"

class Level
{

public:
	// Constructor and deconstructor
	Level(sf::RenderWindow* hwnd, sf::TcpSocket* socket, float* sTime, Input* input);
	~Level();

	// Game loop functions
	void handleInput(float dt);
	void update(sf::TcpSocket& socket, float dt);
	void render();

	// Render functions
	void beginDraw();
	void endDraw();

	// Ghosts variables
	Ghosts ghosts;

	// PacMan variables
	PacMan pacman;

	// UI Variables
	UI timeDisplay;
	UI header;

	// Network Variables
	sf::Packet packet;
	std::string msg;
	Networking network;
	bool correctIP;

	// Initialising camera
	sf::View camera;

	// Ball Variables
	Balls balls;
	
	// Window Variables
	sf::RenderWindow* window;

};
