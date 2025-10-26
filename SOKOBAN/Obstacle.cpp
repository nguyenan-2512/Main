#include "Obstacle.h"

Obstacle::Obstacle() : GameObject(0, 0, 0) {
}
Obstacle::Obstacle(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}