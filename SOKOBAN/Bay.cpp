#include "Bay.h"

Bay::Bay()
    : DoiTuongTroChoi(0, 0, 0),
    dangKichHoat(true),  
    ketCauKichHoat(nullptr),
    ketCauKhongKichHoat(nullptr) {
}

Bay::Bay(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    dangKichHoat(true),
    ketCauKichHoat(nullptr),
    ketCauKhongKichHoat(nullptr) {
}

void Bay::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void Bay::datKichHoat(bool kichHoat) {
    dangKichHoat = kichHoat;
    capNhatKetCau();
}

void Bay::datKetCauKichHoat(const sf::Texture& ketCau) {
    ketCauKichHoat = &ketCau;
    if (dangKichHoat) {
        sprite.setTexture(ketCau);
    }
}

void Bay::datKetCauKhongKichHoat(const sf::Texture& ketCau) {
    ketCauKhongKichHoat = &ketCau;
    if (!dangKichHoat) {
        sprite.setTexture(ketCau);
    }
}

void Bay::capNhatKetCau() {
    if (dangKichHoat && ketCauKichHoat) {
        sprite.setTexture(*ketCauKichHoat);
    }
    else if (!dangKichHoat && ketCauKhongKichHoat) {
        sprite.setTexture(*ketCauKhongKichHoat);
    }
}

bool Bay::layTrangThaiKichHoat() const {
    return dangKichHoat;
}