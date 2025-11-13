#include "CongDichChuyen.h"

CongDichChuyen::CongDichChuyen()
    : DoiTuongTroChoi(0, 0, 0),
    maSoDichChuyen(0),
    ketCau(nullptr) {
}

CongDichChuyen::CongDichChuyen(int x, int y, int kichThuocO, int maSo)
    : DoiTuongTroChoi(x, y, kichThuocO),
    maSoDichChuyen(maSo),
    ketCau(nullptr) {
}

void CongDichChuyen::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void CongDichChuyen::datKetCau(const sf::Texture& ketCau) {
    this->ketCau = &ketCau;
    sprite.setTexture(ketCau);
}