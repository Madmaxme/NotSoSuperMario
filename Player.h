#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name = "Mario", int health = 100, int score = 0, int powerLevel = 3); // initializes player settings with default values

    std::string getName() const; // gets player name
    int getHealth() const; // gets player health
    int getScore() const; // gets player score
    void setName(const std::string& name); // sets player name
    void setHealth(int health); // sets player health
    void setScore(int score); // sets player score
    void takeDamage(int damage); // decreases player health by damage
    void addScore(int points); // increases score by points
    bool isAlive() const; // checks if player is alive based on health

    int getLives() const; // gets current number of lives
    void increaseLives(); // increases lives by one
    void decreaseLives(int decrement = 1); // decreases lives by decrement

    // Methods for game interactions
    void collectCoin(); // adds a coin to the total
    int getCoin() const; // gets total coins collected
    void collectMushroom(); // increases power level
    void enemyDefeated(); // increments score or other benefits
    void loss(); // decrements points or lives
    
private:
    std::string name; // player name
    int health; // player health
    int score; // player score
    int coins; // total coins collected
    int mushrooms; // total mushrooms collected
    int powerLevel; // player power level or lives
    int enemiesDefeated = 0; // number of enemies defeated
};

#endif
