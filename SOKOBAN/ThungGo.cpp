#include "ThungGo.h"

ThungGo::ThungGo()
    : DoiTuongTroChoi(0, 0, 0),
    dangTrenViTriDat(false),
    ketCauBinhThuong(nullptr),
    ketCauTrenViTriDat(nullptr) {
}

ThungGo::ThungGo(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    dangTrenViTriDat(false),
    ketCauBinhThuong(nullptr),
    ketCauTrenViTriDat(nullptr) {
}

void ThungGo::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void ThungGo::datTrangThaiTrenViTriDat(bool trenViTriDat) {
    dangTrenViTriDat = trenViTriDat;
    capNhatKetCau();
}

bool ThungGo::layTrangThaiTrenViTriDat() const {
    return dangTrenViTriDat;
}

void ThungGo::datKetCauBinhThuong(const sf::Texture& ketCau) {
    ketCauBinhThuong = &ketCau;
    if (!dangTrenViTriDat) {
        sprite.setTexture(ketCau);
    }
}

void ThungGo::datKetCauTrenViTriDat(const sf::Texture& ketCau) {
    ketCauTrenViTriDat = &ketCau;
    if (dangTrenViTriDat) {
        sprite.setTexture(ketCau);
    }
}

void ThungGo::capNhatKetCau() {
    if (dangTrenViTriDat && ketCauTrenViTriDat) {
        sprite.setTexture(*ketCauTrenViTriDat);
    }
    else if (!dangTrenViTriDat && ketCauBinhThuong) {
        sprite.setTexture(*ketCauBinhThuong);
    }
}