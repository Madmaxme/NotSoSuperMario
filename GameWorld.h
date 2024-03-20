#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "Player.h"


class GameWorld {
public:
    GameWorld(int worldSize, int maxLevel, int percentCoins, int percentMushrooms, int percentGoomba, int percentKoopa, int initialLives); // Initializes game world settings
    virtual ~GameWorld(); // // Cleans up resources
    void generateEnvironment(); // Generates game world layout
    void populateEntities(double coinsRatio, double mushroomsRatio, double goombasRatio, double koopasRatio); //Adds entities to game world
    void movePlayer(); //Moves the player character
    int findPlayerColumn() const; //Find the players character column
    int findPlayerRow() const; // Find the characters row
    bool interactWithEntity(int row, int column); // Handles interaction with game entities
    void advanceLevel(); // progress to next level
    void updateMoveOutcome(int row, int column); // update the game state after a move
    void placeEntity(int count, char entityType); //places entities in the world
    bool hasPlayerWon() const; //checks if player has won
    void displayWorld() const; //displays the game world
    int getMarioPowerLevel() const; //gets mario power level and life
    void checkGameOver() const; //checks for game over condition
    int getMarioCoins() const; //gets the number of coins collect by mario
    bool isMarioPlaced() const; //checks if matio has been places on array
    std::string getNextMoveDirection() const; //prints marios next move


    int currentLevel; // gets the current game level

private:
    int worldSize; //size of game world
    int maxLevel; //max game level
    int coinsCount; // counts coins
    int mushroomsCount; // counts mushrooms
    int emptySpacesCount; // counts empty space
    int goombasCount; // count goombas
    int koopasCount; // counts koopas
    double coinsRatio; //coins of entities to total
    double mushroomsRatio; //mushrooms of entities to total
    double goombasRatio; // goombas of entities to total
    double koopasRatio; //koopas of entities to total
    char** worldGrid; //game world of grid
    Player playerCharacter; // playre character
    std::string nextMoveDirection;; // displays next moving direction
};

#endif 
