#pragma once
#include <SFML/Graphics.hpp>

enum class MenuAction {
    KHONG,
    CHOI,
    HUONG_DAN,
    THOAT
};

class MenuUI {
private:

    sf::Texture ketCauNen;
    sf::Sprite anhNen;
    sf::RectangleShape nutChoi;
    sf::RectangleShape nutHuongDan;
    sf::RectangleShape nutThoat;

    int mucDaChon;

    bool chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot);
    void thieLapCacNut();

public:
    MenuUI();
    ~MenuUI() = default;
    bool taiTaiNguyen();
    MenuAction xuLySuKien(const sf::Event& suKien);
    void capNhat();
    void ve(sf::RenderWindow& cuaSo);
    void datLai() { mucDaChon = 0; }
};