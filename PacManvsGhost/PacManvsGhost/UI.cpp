#include "UI.h"


UI::UI()
{

	// Load in Font
	if (!gameTimeFont.loadFromFile("D:/Abertay/YEAR3/Networking/Assets/GameText/ARCADECLASSIC.TTF"))
	{
		std::cout << "Error loading from file - text" << endl;
	}

	// Set up each UI Element
	gameTimeText.setFont(gameTimeFont);
	gameTimeText.setCharacterSize(24);
	gameTimeText.setFillColor(sf::Color::White);
	gameTimeText.setStyle(sf::Text::Bold);
	gameTimeText.setPosition(520, 50);

	HeaderText.setFont(gameTimeFont);
	HeaderText.setCharacterSize(36);
	HeaderText.setFillColor(sf::Color::White);
	HeaderText.setStyle(sf::Text::Bold);
	HeaderText.setPosition(500, 10);
	HeaderText.setString("PacMan!");

}

// Render Time
const sf::Text& UI::renderTime(sf::Time elapsedTime)
{
	// Sets a string that only shows the exact Second of the time
	gameTimeText.setString("Time " + std::to_string(static_cast<int>(elapsedTime.asSeconds())));
	return gameTimeText;
}

// Render Header
const sf::Text& UI::renderHeader()
{
	// Renders PacMan! 
	return HeaderText;
}