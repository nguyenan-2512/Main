#include "Tuong.h"

Tuong::Tuong() : DoiTuongTroChoi(0, 0, 0) {
}

Tuong::Tuong(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void Tuong::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}