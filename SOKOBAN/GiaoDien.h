#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"
#include "HuongDan.h"

enum class TrangThaiGiaoDien {
    MENU,
    CHON_BAN_DO,
    HUONG_DAN,
    DANG_CHOI,
    THOAT
};

class GiaoDien {
private:
    HuongDan huongDan;

    sf::CircleShape nutQuayLai;
    bool daNhanQuayLai;

    sf::Texture ketCauNen;
    sf::Sprite anhNen;
    sf::Font chuPhong;
    sf::RectangleShape nutChoi;
    sf::RectangleShape nutHuongDan;
    sf::RectangleShape nutThoat;
    int mucDaChon;
    TrangThaiGiaoDien trangThaiHienTai;

    sf::Texture ketCauNenChonBanDo;
    sf::Sprite anhNenChonBanDo;
    DynamicArray<sf::RectangleShape> cacNutBanDo;
    int banDoDaChon = -1;
    int chiSoBanDoNoi = 0;

public:
    GiaoDien();
    ~GiaoDien();
    bool taiTaiNguyen();
    void xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo);
    void capNhat();
    void ve(sf::RenderWindow& cuaSo);
    TrangThaiGiaoDien layTrangThai() const;
    void datTrangThai(TrangThaiGiaoDien trangThai);
    void datLai();
    int layMapDaChon() const;

private:
    void thieLapCacNut();
    bool chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot);
    bool chuotDeLenNutTron(const sf::CircleShape& nut, sf::Vector2i viTriChuot);

    void thieLapChonBanDo(sf::RenderWindow& cuaSo);
    void veManHinhChonBanDo(sf::RenderWindow& cuaSo);
};