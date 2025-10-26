#include "Goal.h"

Goal::Goal() : GameObject(0, 0, 0) {
}
Goal::Goal(int x, int y, int tileSize) : GameObject(x, y, tileSize) {
}

void Goal::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}