#include "Player.h"

Player::Player(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    currentState(Animation::MOVE_DOWN) {  
}

void Player::initAnimation(const sf::Texture& spriteSheet,
    int frameWidth,
    int frameHeight,
    int numFrames) {
    animation = Animation(&sprite, spriteSheet, frameWidth, frameHeight, numFrames, true);
}

void Player::update(float deltaTime) {
    animation.update(currentState, deltaTime);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::move(int dx, int dy) {
    if (dy < 0) {
        currentState = Animation::MOVE_UP;     
    }
    else if (dy > 0) {
        currentState = Animation::MOVE_DOWN;   
    }
    else if (dx < 0) {
        currentState = Animation::MOVE_LEFT;  
    }
    else if (dx > 0) {
        currentState = Animation::MOVE_RIGHT;  
    }
}

void Player::setPosition(int x, int y, int dx, int dy) {
    move(dx, dy);
    GameObject::setPosition(x, y);
}