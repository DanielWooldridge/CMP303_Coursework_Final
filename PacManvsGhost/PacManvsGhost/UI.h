#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "PacMan.h"
#include "Ghosts.h"
class UI
{
public:

	// UI Functions
	UI();
	const sf::Text& renderTime(sf::Time liveGameTime);
	const sf::Text& renderHeader();

private:

	// Font and Text variables
	sf::Font gameTimeFont;
	sf::Text gameTimeText;
	sf::Text HeaderText;
};

