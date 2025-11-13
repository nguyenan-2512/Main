#include "HoatHinh.h"
#include <iostream>

float HoatHinh::tocDoHoatHinh = 0.1f;

HoatHinh::HoatHinh()
    : sprite(nullptr),
    chieuRongKhung(0),
    chieuCaoKhung(0),
    khungHienTai(0),
    trangThaiHienTai(-1),
    lapLai(true) {
}

HoatHinh::HoatHinh(sf::Sprite* sprite,
    const sf::Texture& bangAnh,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh,
    bool lapLai)
    : sprite(sprite),
    bangAnh(bangAnh),
    chieuRongKhung(chieuRongKhung),
    chieuCaoKhung(chieuCaoKhung),
    khungHienTai(0),
    trangThaiHienTai(-1),
    lapLai(lapLai) {

    // Chia sprite sheet thành các frame cho từng hướng
    for (int i = 0; i < soKhungHinh; ++i) {
        // Hàng 0: Di chuyển XUỐNG (mặt)
        cacKhungDiXuong.push_back(
            sf::IntRect(i * chieuRongKhung, 0, chieuRongKhung, chieuCaoKhung)
        );

        // Hàng 1: Di chuyển LÊN (lưng)
        cacKhungDiLen.push_back(
            sf::IntRect(i * chieuRongKhung, chieuCaoKhung, chieuRongKhung, chieuCaoKhung)
        );

        // Hàng 2: Di chuyển trái
        cacKhungDiTrai.push_back(
            sf::IntRect(i * chieuRongKhung, 2 * chieuCaoKhung, chieuRongKhung, chieuCaoKhung)
        );

        // Hàng 3: Di chuyển phải
        cacKhungDiPhai.push_back(
            sf::IntRect(i * chieuRongKhung, 3 * chieuCaoKhung, chieuRongKhung, chieuCaoKhung)
        );
    }

    // Thiết lập texture và frame ban đầu
    if (sprite) {
        sprite->setTexture(bangAnh);
        sprite->setTextureRect(cacKhungDiXuong[0]);
    }
}

void HoatHinh::capNhat(const int& trangThai, float thoiGianDelta) {
    if (!sprite) return;

    // Nếu trạng thái thay đổi → Reset animation
    if (trangThai != trangThaiHienTai) {
        trangThaiHienTai = trangThai;
        khungHienTai = 0;
        dongHoKhung.restart();
    }

    // Cập nhật frame dựa trên thời gian
    if (dongHoKhung.getElapsedTime().asSeconds() >= tocDoHoatHinh) {
        khungHienTai++;
        dongHoKhung.restart();

        // Chọn DynamicArray frame tương ứng với trạng thái
        DynamicArray<sf::IntRect>* cacKhung = nullptr;
        switch (trangThaiHienTai) {
        case DI_LEN:    cacKhung = &cacKhungDiLen; break;
        case DI_XUONG:  cacKhung = &cacKhungDiXuong; break;
        case DI_TRAI:   cacKhung = &cacKhungDiTrai; break;
        case DI_PHAI:   cacKhung = &cacKhungDiPhai; break;
        default:        cacKhung = &cacKhungDiXuong; break;
        }

        if (cacKhung && !cacKhung->empty()) {
            // Kiểm tra nếu vượt quá số frame
            if (khungHienTai >= cacKhung->size()) {
                if (lapLai) {
                    khungHienTai = 0;
                }
                else {
                    khungHienTai = cacKhung->size() - 1;
                }
            }

            // Cập nhật texture rect
            sprite->setTextureRect((*cacKhung)[khungHienTai]);
        }
    }
}

void HoatHinh::datLai() {
    khungHienTai = 0;
    dongHoKhung.restart();
}