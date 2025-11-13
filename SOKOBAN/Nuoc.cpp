#include "Nuoc.h"

Nuoc::Nuoc() : DoiTuongTroChoi(0, 0, 0) {
}

Nuoc::Nuoc(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void Nuoc::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}