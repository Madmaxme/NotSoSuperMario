#include "GameWorld.h"
#include "Player.h"
#include "FileProcessor.h"
#include <iostream>
#include <fstream>
#include <streambuf>

int main(int argc, char* argv[]) {
    // Checking command line args for config file
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputConfigFile>" << std::endl;
        return 1;
    }

    // Setting up file paths and file processor
    std::string inputPath = argv[1];
    FileProcessor fileProcessor("output.txt");

    // Redirecting cout to output file
    std::ofstream out("output.txt");
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());

    // Declaring game settings
    int maxLevel, worldSize, initialLives;
    int percentCoins, percentNothing, percentGoombas, percentKoopas, percentMushrooms;

    // Reading game config
    if (!fileProcessor.readConfig(inputPath, maxLevel, worldSize, initialLives, 
                                  percentCoins, percentNothing, percentGoombas, percentKoopas, percentMushrooms)) {
        std::cout << "Couldn't read config." << std::endl;
        return 1;
    }

    // Game setup done
    std::cout << "Game ready" << std::endl;

    // Creating game world and Mario
    GameWorld world(worldSize, maxLevel, percentCoins, percentMushrooms, percentGoombas, percentKoopas, initialLives);
    Player Mario("Mario", 100, 0, initialLives);

    // Starting first level
    world.advanceLevel();
    std::cout << "Level setup done" << std::endl;
    world.displayWorld();

    // Main game loop
    int i = 0;
    int moveWithoutProgress = 0;
    const int someThreshold = 10;

    while (Mario.isAlive()) {
        // Printing game stats
        std::cout << "Level: " << world.currentLevel << std::endl;
        std::cout << "Mario at: " << world.findPlayerRow() << ", " << world.findPlayerColumn() << std::endl;
        std::cout << "Lives left: " << world.getMarioPowerLevel() << std::endl;
        world.movePlayer(); 
        world.displayWorld();
        world.hasPlayerWon();
        std::cout << "Lives: " << world.getMarioPowerLevel() << std::endl;
        std::cout << "Coins: " << world.getMarioCoins() << std::endl;
        std::cout << "Next move: " << world.getNextMoveDirection() << std::endl;
        std::cout << "----------------" << std::endl;
        i++; 

        // Progress check
        if (moveWithoutProgress > someThreshold) {
            moveWithoutProgress = 0; 
        } else {
            moveWithoutProgress++;
        }
    }

    // Game over message
    std::cout << "Game Over. Mario's out of lives." << std::endl;

    // Reset cout to original buffer
    std::cout.rdbuf(coutBuf);

    return 0;
}
