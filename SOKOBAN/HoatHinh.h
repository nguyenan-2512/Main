#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class HoatHinh {
private:
    sf::Sprite* sprite;
    sf::Texture bangAnh; 
    sf::Clock dongHoKhung;

    int chieuRongKhung;
    int chieuCaoKhung;
    int khungHienTai;
    int trangThaiHienTai;
    bool lapLai;  

    DynamicArray<sf::IntRect> cacKhungDiLen;
    DynamicArray<sf::IntRect> cacKhungDiXuong;
    DynamicArray<sf::IntRect> cacKhungDiTrai;
    DynamicArray<sf::IntRect> cacKhungDiPhai;

public:
    static float tocDoHoatHinh;  


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