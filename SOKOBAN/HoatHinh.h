#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class HoatHinh {
private:
    sf::Sprite* sprite;
    sf::Texture bangAnh;  // Sprite sheet

    int chieuRongKhung;
    int chieuCaoKhung;
    int khungHienTai;
    int trangThaiHienTai;
    bool lapLai;  // Có lặp lại animation không

    sf::Clock dongHoKhung;  // Đếm thời gian giữa các frame

    // Các frame cho mỗi hướng di chuyển
    DynamicArray<sf::IntRect> cacKhungDiLen;
    DynamicArray<sf::IntRect> cacKhungDiXuong;
    DynamicArray<sf::IntRect> cacKhungDiTrai;
    DynamicArray<sf::IntRect> cacKhungDiPhai;

public:
    static float tocDoHoatHinh;  // Tốc độ chuyển frame (giây)

    // Các trạng thái di chuyển
    enum TrangThai {
        DI_LEN = 0,
        DI_XUONG = 1,
        DI_TRAI = 2,
        DI_PHAI = 3
    };

    HoatHinh();

    HoatHinh(sf::Sprite* sprite,
        const sf::Texture& bangAnh,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh,
        bool lapLai = true);

    void capNhat(const int& trangThai, float thoiGianDelta);
    void datLai();

    int layKhungHienTai() const { return khungHienTai; }
    int layTrangThaiHienTai() const { return trangThaiHienTai; }
};