#include "NutBam.h"

NutBam::NutBam()
    : DoiTuongTroChoi(0, 0, 0),
    dangDuocNhan(false),
    ketCauChuaNhan(nullptr),
    ketCauDaNhan(nullptr) {
}

NutBam::NutBam(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    dangDuocNhan(false),
    ketCauChuaNhan(nullptr),
    ketCauDaNhan(nullptr) {
}

void NutBam::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void NutBam::datTrangThaiNhan(bool duocNhan) {
    dangDuocNhan = duocNhan;
    capNhatKetCau();
}

void NutBam::datKetCauChuaNhan(const sf::Texture& ketCau) {
    ketCauChuaNhan = &ketCau;
    if (!dangDuocNhan) {
        sprite.setTexture(ketCau);
    }
}

void NutBam::datKetCauDaNhan(const sf::Texture& ketCau) {
    ketCauDaNhan = &ketCau;
    if (dangDuocNhan) {
        sprite.setTexture(ketCau);
    }
}

void NutBam::capNhatKetCau() {
    if (dangDuocNhan && ketCauDaNhan) {
        sprite.setTexture(*ketCauDaNhan);
    }
    else if (!dangDuocNhan && ketCauChuaNhan) {
        sprite.setTexture(*ketCauChuaNhan);
    }
}