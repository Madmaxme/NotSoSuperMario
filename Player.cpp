#include "Player.h"
#include <iostream>

Player::Player(const std::string& name, int health, int score, int powerLevel)
    : name(name), health(health), score(score), coins(0), mushrooms(0), powerLevel(powerLevel) {
}

std::string Player::getName() const {
    return name;
}

int Player::getHealth() const {
    return health;
}

int Player::getScore() const {
    return score;
}

void Player::setName(const std::string& newName) {
    name = newName;
}

void Player::setHealth(int newHealth) {
    health = newHealth;
}

void Player::setScore(int newScore) {
    score = newScore;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health <= 0) {
        decreaseLives(1); 
    }
}

void Player::addScore(int points) {
    score += points;
}

bool Player::isAlive() const {
    return powerLevel > 0;
}

int Player::getLives() const {
    return powerLevel;
}

void Player::increaseLives() {
    if (powerLevel < 3) {
        powerLevel++;
        std::cout << "Mario's lives increased to: " << powerLevel << std::endl;
    }
}

void Player::decreaseLives(int decrement) {
    powerLevel -= decrement;
    if (powerLevel < 0) {
        powerLevel = 0; 
    }
    std::cout << "Mario's lives decreased to: " << powerLevel << std::endl;
}

void Player::collectCoin() {
    coins++;

    if(coins == 20) {
        coins = 0;
        increaseLives();
        std::cout << "Mario gains a life for collecting 20 coins!" << std::endl;
    }
}

int Player::getCoin() const {
    return coins;
}

void Player::collectMushroom() {
    mushrooms++;
    setHealth(getHealth() + 20); 
    increaseLives();
}

void Player::enemyDefeated() {
    if(enemiesDefeated == 7){
        increaseLives();
        enemiesDefeated = 0;
        std::cout << "Mario gained an extra life!" << std::endl;
    }
}

void Player::loss() {
    takeDamage(10); 
}
