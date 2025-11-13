#include "Nen.h"

Nen::Nen() : DoiTuongTroChoi(0, 0, 0) {
}

Nen::Nen(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void Nen::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}