#include "Balls.h"


Balls::Balls()
{
	// Seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(nullptr)));
}

sf::Vector2f Balls::randomPositionGenerator()
{
	// Generate 2 different Values, one for each axis
	auto randomNumberX = rand() % 1200;
	auto randomNumberY = rand() % 675;
	// Store in a vector
	return sf::Vector2f(randomNumberX, randomNumberY);
}