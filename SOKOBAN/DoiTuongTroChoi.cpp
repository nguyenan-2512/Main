#include "DoiTuongTroChoi.h"

DoiTuongTroChoi::DoiTuongTroChoi(int x, int y, int kichThuocO)
    : viTri(x, y), kichThuocO(kichThuocO) {
    sprite.setPosition(
        static_cast<float>(x * kichThuocO),
        static_cast<float>(y * kichThuocO)
    );
}

Diem DoiTuongTroChoi::layViTri() const {
    return viTri;
}

int DoiTuongTroChoi::layX() const {
    return viTri.layX();
}

int DoiTuongTroChoi::layY() const {
    return viTri.layY();
}

void DoiTuongTroChoi::datViTri(int x, int y) {
    viTri.datXY(x, y);
    sprite.setPosition(
        static_cast<float>(x * kichThuocO),
        static_cast<float>(y * kichThuocO)
    );
}

void DoiTuongTroChoi::datKetCau(const sf::Texture& ketCau) {
    sprite.setTexture(ketCau);
}