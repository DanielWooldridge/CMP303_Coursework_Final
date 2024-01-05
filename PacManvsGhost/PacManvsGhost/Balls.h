#pragma once
#include "Framework/GameObject.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "PacMan.h"
#include <SFML/Network.hpp>
#include "Framework/Collision.h"

class PacMan;

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
