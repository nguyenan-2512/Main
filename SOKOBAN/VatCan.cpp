#include "VatCan.h"

VatCan::VatCan() : DoiTuongTroChoi(0, 0, 0) {}

VatCan::VatCan(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {}

void VatCan::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}