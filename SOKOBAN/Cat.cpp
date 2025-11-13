#include "Cat.h"

Cat::Cat() : DoiTuongTroChoi(0, 0, 0) {
}

Cat::Cat(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void Cat::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}