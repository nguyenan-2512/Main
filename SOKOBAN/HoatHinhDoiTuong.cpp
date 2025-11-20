#include "HoatHinhDoiTuong.h"
#include <iostream>

HoatHinhDoiTuong::HoatHinhDoiTuong()
    : sprite(nullptr),
    chieuRongKhung(0),
    chieuCaoKhung(0),
    soKhungHinh(0),
    khungHienTai(0),
    tocDoHoatHinh(0.1f),
    lapLai(true),
    dangChay(true) {
}

HoatHinhDoiTuong::HoatHinhDoiTuong(sf::Sprite* sprite,
    const sf::Texture& bangAnh,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh,
    float tocDoHoatHinh,
    bool lapLai)
    : sprite(sprite),
    bangAnh(bangAnh),
    chieuRongKhung(chieuRongKhung),
    chieuCaoKhung(chieuCaoKhung),
    soKhungHinh(soKhungHinh),
    khungHienTai(0),
    tocDoHoatHinh(tocDoHoatHinh),
    lapLai(lapLai),
    dangChay(true) {

    if (sprite) {
        sprite->setTexture(bangAnh);
        taoKhungHinh();

        if (!cacKhung.empty()) {
            sprite->setTextureRect(cacKhung[0]);
        }
    }
}

bool HoatHinhDoiTuong::khoiTao(sf::Sprite* sprite,
    const std::string& duongDanTexture,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh,
    float tocDoHoatHinh,
    bool lapLai) {
    this->sprite = sprite;
    this->chieuRongKhung = chieuRongKhung;
    this->chieuCaoKhung = chieuCaoKhung;
    this->soKhungHinh = soKhungHinh;
    this->tocDoHoatHinh = tocDoHoatHinh;
    this->lapLai = lapLai;
    this->khungHienTai = 0;
    this->dangChay = true;

    if (!bangAnh.loadFromFile(duongDanTexture)) {
        std::cerr << "Khong the tai texture: " << duongDanTexture << std::endl;
        return false;
    }

    if (sprite) {
        sprite->setTexture(bangAnh);
        taoKhungHinh();

        if (!cacKhung.empty()) {
            sprite->setTextureRect(cacKhung[0]);
        }
    }

    return true;
}

void HoatHinhDoiTuong::taoKhungHinh() {
    cacKhung.clear();

    // Tạo các frame từ spritesheet (theo hàng ngang)
    for (int i = 0; i < soKhungHinh; i++) {
        int x = (i * chieuRongKhung) % static_cast<int>(bangAnh.getSize().x);
        int y = ((i * chieuRongKhung) / static_cast<int>(bangAnh.getSize().x)) * chieuCaoKhung;

        cacKhung.push_back(sf::IntRect(x, y, chieuRongKhung, chieuCaoKhung));
    }
}

void HoatHinhDoiTuong::capNhat(float thoiGianDelta) {
    if (!sprite || !dangChay || cacKhung.empty()) {
        return;
    }

    // Kiểm tra xem đã đến lúc chuyển frame chưa
    if (dongHoKhung.getElapsedTime().asSeconds() >= tocDoHoatHinh) {
        khungHienTai++;

        // Xử lý khi hết frame
        if (khungHienTai >= soKhungHinh) {
            if (lapLai) {
                khungHienTai = 0;  // Quay lại frame đầu
            }
            else {
                khungHienTai = soKhungHinh - 1;  // Dừng ở frame cuối
                dangChay = false;
            }
        }

        // Cập nhật texture rect
        sprite->setTextureRect(cacKhung[khungHienTai]);
        dongHoKhung.restart();
    }
}

void HoatHinhDoiTuong::batDau() {
    dangChay = true;
    dongHoKhung.restart();
}

void HoatHinhDoiTuong::tamDung() {
    dangChay = false;
}

void HoatHinhDoiTuong::datLai() {
    khungHienTai = 0;
    dangChay = true;
    dongHoKhung.restart();

    if (sprite && !cacKhung.empty()) {
        sprite->setTextureRect(cacKhung[0]);
    }
}

void HoatHinhDoiTuong::datTocDo(float tocDo) {
    tocDoHoatHinh = tocDo;
}