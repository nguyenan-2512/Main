#include "ThungSat.h"

ThungSat::ThungSat()
    : DoiTuongTroChoi(0, 0, 0),
    ketCau(nullptr) {
}

ThungSat::ThungSat(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    ketCau(nullptr) {
}

void ThungSat::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void ThungSat::datKetCauThungSat(const sf::Texture& ketCau) {
    this->ketCau = &ketCau;
    sprite.setTexture(ketCau);
}