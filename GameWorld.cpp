#include "GameWorld.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

GameWorld::GameWorld(int worldSize, int maxLevel, int pc, int pm, int pg, int pk, int initialLives)
    : worldSize(worldSize),
      maxLevel(maxLevel),
      coinsRatio(pc / 100.0),
      mushroomsRatio(pm / 100.0),
      goombasRatio(pg / 100.0),
      koopasRatio(pk / 100.0),
      currentLevel(0),
      playerCharacter(Player("Mario", 100, 0, initialLives)), // Initialize playerCharacter with initialLives
      worldGrid(nullptr) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); 
}

GameWorld::~GameWorld() {
    for (int i = 0; i < worldSize; i++) {
        delete[] worldGrid[i];
    }
    delete[] worldGrid;
    std::cout << "GameWorld has been deallocated" << std::endl;
}

void GameWorld::generateEnvironment() {
    worldGrid = new char*[worldSize];
    for (int i = 0; i < worldSize; i++) {
        worldGrid[i] = new char[worldSize];
        std::fill(worldGrid[i], worldGrid[i] + worldSize, 'x');
    }
}

void GameWorld::advanceLevel() {
    if (currentLevel > 0) {
        for (int i = 0; i < worldSize; i++) {
            delete[] worldGrid[i];
        }
        delete[] worldGrid;
        worldGrid = nullptr;
    }
    currentLevel++;
    generateEnvironment();
    populateEntities(coinsRatio, mushroomsRatio, goombasRatio, koopasRatio);
    if (currentLevel <= maxLevel) {
        std::cout << "Advancing to level " << currentLevel << std::endl;
        std::cout << "+ + + + + + + + + + + +" << std::endl;
    }
}

void GameWorld::displayWorld() const {
    for (int i = 0; i < worldSize; i++) {
        for (int j = 0; j < worldSize; j++) {
            std::cout << worldGrid[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int GameWorld::getMarioPowerLevel() const {
    return playerCharacter.getLives();
}

int GameWorld::getMarioCoins() const {
    return playerCharacter.getCoin(); 
}



int GameWorld::findPlayerRow() const {
    for (int i = 0; i < worldSize; i++) {
        for (int j = 0; j < worldSize; j++) {
            if (worldGrid[i][j] == 'H') {
                return i;
            }
        }
    }
    return -1;
}

int GameWorld::findPlayerColumn() const {
    for (int i = 0; i < worldSize; i++) {
        for (int j = 0; j < worldSize; j++) {
            if (worldGrid[i][j] == 'H') {
                return j;
            }
        }
    }
    return -1;
}

bool GameWorld::interactWithEntity(int row, int column) {
    int chance = std::rand() % 100;
    char entity = worldGrid[row][column];
    switch (entity) {
        case 'x': // Empty space
            std::cout << "The position is empty." << std::endl;
            return true;

        case 'c': // Coin
            playerCharacter.collectCoin();
            std::cout << "Mario collected a coin!" << std::endl;
            return true;

        case 'm': // Mushroom
            playerCharacter.collectMushroom();
            std::cout << "Mario collected a mushroom!" << std::endl;
            playerCharacter.increaseLives();            return true;

        case 'g': // Goomba
            if (chance <= 80) {
                std::cout << "Mario defeated a Goomba!" << std::endl;
                playerCharacter.enemyDefeated();
                return true;
            } else {
                std::cout << "Mario lost to a Goomba." << std::endl;
                playerCharacter.decreaseLives();
                playerCharacter.loss();
                if (!playerCharacter.isAlive()) {
                    checkGameOver(); // Check if the game is over
                }
                return false;
            }

        case 'k': // Koopa
            if (chance <= 60) {
                std::cout << "Mario defeated a Koopa!" << std::endl;
                playerCharacter.enemyDefeated();
                return true;
            } else {
                std::cout << "Mario lost to a Koopa." << std::endl;
                std::cout << "Mario has lost power." << std::endl;
                playerCharacter.decreaseLives();
                playerCharacter.loss();
                if (!playerCharacter.isAlive()) {
                    checkGameOver(); // Check if the game is over
                }
                return false;
            }

       case 'b': // Boss
        std::cout << "Mario encountered the Boss!" << std::endl;
        if (chance <= 50) {
            std::cout << "Mario defeated the Boss!" << std::endl;
            advanceLevel();
            return true; 
        } else {
            std::cout << "Mario lost to the Boss." << std::endl;
            playerCharacter.decreaseLives(2); 
            if (!playerCharacter.isAlive()) {
                checkGameOver(); 
            }
            return false; 
        }


        case 'w': // Warp Pipe
            std::cout << "Mario found a Warp Pipe!" << std::endl;
            advanceLevel();
            return true;

        default:
            std::cout << "Encountered an unknown entity." << std::endl;
            return false;
    }
}


void GameWorld::updateMoveOutcome(int row, int column) {
    int playerRow = findPlayerRow();
    int playerColumn = findPlayerColumn();
    if (interactWithEntity(row, column)) {
        worldGrid[playerRow][playerColumn] = 'x';
        worldGrid[row][column] = 'H';
    } else {
        std::cout << "Mario stays still." << std::endl;
    }
}

void GameWorld::movePlayer() {
    int direction = std::rand() % 4; // 0: up, 1: right, 2: down, 3: left
    int newRow = findPlayerRow();
    int newColumn = findPlayerColumn();

    // Determine and log the next movement direction
    switch (direction) {
        case 0: // Up
            nextMoveDirection = "UP";
            newRow = (newRow == 0) ? worldSize - 1 : newRow - 1; // Wrap around if necessary
            break;
        case 1: // Right
            nextMoveDirection = "RIGHT";
            newColumn = (newColumn == worldSize - 1) ? 0 : newColumn + 1; // Wrap around if necessary
            break;
        case 2: // Down
            nextMoveDirection = "DOWN";
            newRow = (newRow == worldSize - 1) ? 0 : newRow + 1; // Wrap around if necessary
            break;
        case 3: // Left
            nextMoveDirection = "LEFT";
            newColumn = (newColumn == 0) ? worldSize - 1 : newColumn - 1; // Wrap around if necessary
            break;
        default:
            nextMoveDirection = "STAY PUT"; // Fallback case
            break;
    }

    // Continue with the movement logic
    // This may involve updating Mario's position in the game world grid,
    // handling interactions at the new position, etc.
    updateMoveOutcome(newRow, newColumn); // Example function call to handle the move outcome
}


bool GameWorld::hasPlayerWon() const {
    if (currentLevel > maxLevel) {
        std::cout << "The princess has been saved!" << std::endl;
        std::exit(0);
    }
    return false;
}

void GameWorld::checkGameOver() const {
    if (!playerCharacter.isAlive()) {
        std::cout << "Game Over. Mario has no lives left." << std::endl;
        exit(0);
        
    }
}

bool GameWorld::isMarioPlaced() const {
    for (int i = 0; i < worldSize; i++) {
        for (int j = 0; j < worldSize; j++) {
            if (worldGrid[i][j] == 'H') { 
                return true;
            }
        }
    }
    return false;
}




std::string GameWorld::getNextMoveDirection() const {
    return nextMoveDirection;
}


void GameWorld::populateEntities(double coinsRatio, double mushroomsRatio, double goombasRatio, double koopasRatio) {
    int area = worldSize * worldSize;
    int numCoins = static_cast<int>(coinsRatio * area);
    int numMushrooms = static_cast<int>(mushroomsRatio * area);
    int numGoombas = static_cast<int>(goombasRatio * area);
    int numKoopas = static_cast<int>(koopasRatio * area);
    int numMario = 1;
    int numBoss = (currentLevel == maxLevel) ? 1 : 0; 
    int numPipe = (currentLevel < maxLevel) ? 1 : 0; 

    placeEntity(numCoins, 'c');
    placeEntity(numMushrooms, 'm');
    placeEntity(numGoombas, 'g');
    placeEntity(numKoopas, 'k');
    placeEntity(numBoss, 'b');
    placeEntity(numPipe, 'w');
    if (!isMarioPlaced()) {
        placeEntity(numMario, 'H');
    }
    
}

void GameWorld::placeEntity(int count, char entityType) {
    while (count > 0) {
        int randRow = std::rand() % worldSize;
        int randColumn = std::rand() % worldSize;

        if (worldGrid[randRow][randColumn] == 'x') {
            worldGrid[randRow][randColumn] = entityType;
            count--;
        }
    }
}
