#pragma once
#include <SFML/Graphics.hpp>

// Enum định nghĩa hành động từ menu
enum class MenuAction {
    KHONG,
    CHOI,
    HUONG_DAN,
    THOAT
};

// Class quản lý menu chính
class MenuUI {
private:
    // Background
    sf::Texture ketCauNen;
    sf::Sprite anhNen;

    // Buttons
    sf::RectangleShape nutChoi;
    sf::RectangleShape nutHuongDan;
    sf::RectangleShape nutThoat;

    int mucDaChon;

    // Helper functions
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