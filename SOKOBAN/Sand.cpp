#include "Sand.h"

Sand::Sand() : GameObject(0, 0, 0) {
}
Sand::Sand(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Sand::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}