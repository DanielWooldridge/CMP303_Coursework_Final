#pragma once
#include "Framework/GameObject.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Balls :
    public GameObject
{
public:

    Balls();

    // Functions for Ball creation and rendering
    void createBalls(sf::Vector2f positions, int ID);
    void render(sf::RenderWindow& window);

private:

    // Variables used to store the balls and ballIDs
    std::vector<sf::CircleShape>balls;
    std::vector<int> ballIDs;

};