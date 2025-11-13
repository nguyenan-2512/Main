#include "Cau.h"

Cau::Cau() : DoiTuongTroChoi(0, 0, 0) {
}

Cau::Cau(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void Cau::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}