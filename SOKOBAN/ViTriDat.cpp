#include "ViTriDat.h"

ViTriDat::ViTriDat() : DoiTuongTroChoi(0, 0, 0) {
}

ViTriDat::ViTriDat(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO) {
}

void ViTriDat::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}