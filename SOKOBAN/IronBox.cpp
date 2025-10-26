
#include "IronBox.h"

IronBox::IronBox()
    : GameObject(0, 0, 0),
    texture(nullptr) {
}
IronBox::IronBox(int x, int y, int tileSize)
    : GameObject(x, y, tileSize),
    texture(nullptr) {
}

void IronBox::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void IronBox::setIronTexture(const sf::Texture& tex) {
    texture = &tex;
    sprite.setTexture(tex);
}