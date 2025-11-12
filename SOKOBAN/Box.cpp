#include "Box.h"

Box::Box()
    : GameObject(0, 0, 0),
    isOnGoal(false),
    normalTexture(nullptr),
    goalTexture(nullptr) {
}
Box::Box(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    isOnGoal(false),
    normalTexture(nullptr),
    goalTexture(nullptr) {
}

void Box::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Box::setOnGoal(bool onGoal) {
    isOnGoal = onGoal;
    CapNhatTexture();
}

bool Box::getIsOnGoal() const {
    return isOnGoal;
}

void Box::setNormalTexture(const sf::Texture& texture) {
    normalTexture = &texture;
    if (!isOnGoal) {
        sprite.setTexture(texture);
    }
}

void Box::setGoalTexture(const sf::Texture& texture) {
    goalTexture = &texture;
    if (isOnGoal) {
        sprite.setTexture(texture);
    }
}

void Box::CapNhatTexture() {
    if (isOnGoal && goalTexture) {
        sprite.setTexture(*goalTexture);
    }
    else if (!isOnGoal && normalTexture) {
        sprite.setTexture(*normalTexture);
    }
}