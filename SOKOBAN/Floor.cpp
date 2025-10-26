#include "Floor.h"

Floor::Floor() : GameObject(0, 0, 0) {
}
Floor::Floor(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Floor::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}