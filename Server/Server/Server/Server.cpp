#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <thread>
#include "Balls.h"

using namespace std;


// Struct that holds All of the clients Data
struct clientData {
    float xPos[2];
    float yPos[2];
    sf::Int8 clientLabelID[2];
 
};

// Enum Type for each Packet Type - Int8s to make it faster
enum packetIDs : sf::Int8 {

    PT_POSITIONS = 2,
    PT_START = 3,
    PT_BALLS = 4
};


int main() {

    // Variable Creation
    float numOfConnections = 0; // Holds the number of connections
    sf::TcpListener listener;   
    sf::TcpSocket clientOne;    // Sockets for clients
    sf::TcpSocket clientTwo;
    clientData cData;           // Struct Variable to hold client data
    sf::Clock timer;            // Timer
    Balls balls;                // Balls Variable
    timer.restart();
    bool startPacketSent = true;   // Flags to see if different kind of packets have been sent
    bool ballPacketSent = true;

    // CONNECTING TO SERVER //
    // Ask the Server what its local Address is
    sf::IpAddress serverIP = sf::IpAddress::getLocalAddress();
    cout << "Server IP Address: " << serverIP << endl;
    cout << "Listening on Port - 2222" << endl;
    listener.listen(2222, serverIP);

    // Connect a client if these are true
    if (listener.accept(clientOne) == sf::Socket::Done) {

        // Assigning ID from the clients sent string that came with their connection
        // This will tell us who is who
        sf::Packet idPacket;
        clientOne.receive(idPacket);

        std::string clientId;
        idPacket >> clientId;

        std::cout << "Player with ID '" << clientId << "' has joined!" << std::endl;

        if (clientId == "PacMan") {
            cData.clientLabelID[0] = 1;
        }
        else {
            cData.clientLabelID[0] = 2;
        }

        std::cout << " My Client Id is " << cData.clientLabelID[0] << endl;

        // Increment the number of connections
        numOfConnections++;
       
    }

    if (listener.accept(clientTwo) == sf::Socket::Done) {
        sf::Packet idPacket;
        clientTwo.receive(idPacket);

        std::string clientId;
        idPacket >> clientId;

        std::cout << "Player with ID '" << clientId << "' has joined!" << std::endl;

        if (clientId == "PacMan") {
            cData.clientLabelID[1] = 1;
        }
        else {
            cData.clientLabelID[1] = 2;
        }

        std::cout << " My Client Id is " << cData.clientLabelID[1] << endl;

        // Increment the number of connections
        numOfConnections++;
      
    }

  
    // Set both of our clients to not blocking - This will decrease latency
   clientOne.setBlocking(false);
   clientTwo.setBlocking(false);

   // If both Clients are connected
    while (numOfConnections <= 2) {

        // Send Time Packet - This is a one off packet we send to tell the clients to start a game timer
        if (startPacketSent) {
          
            cout << "Sent Time start packet" << endl;
            sf::Packet startPacket;
            startPacket << PT_START;

            if (clientOne.send(startPacket) != sf::Socket::Done) {
                cout << "Error sending start packet to clientOne" << endl;
            }

            if (clientTwo.send(startPacket) != sf::Socket::Done) {
                cout << "Error sending start packet to clientTwo" << endl;
            }

            startPacketSent = false;
            startPacket.clear();
        }


        sf::Packet receivedPacket;
        sf::Packet rpacket;

        // Receive Players position - This gets the data of each players current position on the screen
        if (clientOne.receive(receivedPacket) == sf::Socket::Done) {
            sf::Int8 packetType;
            receivedPacket >> packetType;

            if (packetType == PT_POSITIONS)
            {
                float x, y;
                receivedPacket >> x >> y;

                // Hold the packets information in the client struct variable 
                cData.xPos[0] = x;
                cData.yPos[0] = y;

                receivedPacket.clear();

                // Put the data into a packet with a Packet Type enum variable - this allows the client to know whats inside the packet
                receivedPacket << PT_POSITIONS << cData.xPos[0] << cData.yPos[0];

                // Send this data to the other Client
                clientTwo.send(receivedPacket);
            }
        }
      
        // Receive Players position - This gets the data of each players current position on the screen
        if (clientTwo.receive(rpacket) == sf::Socket::Done) {
            sf::Int8 packetType;
            rpacket >> packetType;

            if (packetType == PT_POSITIONS)
            {
                float x, y;
                rpacket >> x >> y;

                // Hold the packets information in the client struct variable 
                cData.xPos[1] = x;
                cData.yPos[1] = y;

                rpacket.clear();
                // Put the data into a packet with a Packet Type enum variable - this allows the client to know whats inside the packet
                rpacket << PT_POSITIONS << cData.xPos[1] << cData.yPos[1];

                // Send this data to the other Client
                clientOne.send(rpacket);
            }
        }
       
        // Send Ball packet - This generates and holds the balls positions
        if (ballPacketSent)
        {
            // Run 5 Times
            for (int i = 0; i < 5; i++)
            {
                // Get a Random Position
                sf::Vector2f ballPosition = balls.randomPositionGenerator();

                // Output the Balls position
                std::cout << "Generated ball position: " << ballPosition.x << ", " << ballPosition.y << std::endl;

                // Use a packet to send the data of that ball
                sf::Packet ballPacket;

                // Put the data into a packet with a Packet Type enum variable - this allows the client to know whats inside the packet
                ballPacket << PT_BALLS << ballPosition.x << ballPosition.y;
                if (clientOne.send(ballPacket) != sf::Socket::Done) {
                    cout << "Error sending ball packet to clientOne" << endl;
                }

                if (clientTwo.send(ballPacket) != sf::Socket::Done) {
                    cout << "Error sending ball packet to clientTwo" << endl;
                }

            }
            // Reset the value so this wont be sent again after the 5 times
            ballPacketSent = false;
        }

     
    }

    return 0;
}



