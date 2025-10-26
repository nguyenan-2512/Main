#include "Water.h"

Water::Water() : GameObject(0, 0, 0) {
}
Water::Water(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Water::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}