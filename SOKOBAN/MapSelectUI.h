#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

// Class quản lý màn hình chọn map
class MapSelectUI {
private:
    // Background
    sf::Texture ketCauNen;
    sf::Sprite anhNen;

    // Nút quay lại
    sf::CircleShape nutQuayLai;

    // Các nút map
    DynamicArray<sf::RectangleShape> cacNutBanDo;

    int chiSoBanDoNoi;
    int banDoDaChon;

    // Helper functions
    bool chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot);
    bool chuotDeLenNutTron(const sf::CircleShape& nut, sf::Vector2i viTriChuot);
    void thieLapCacNutBanDo();

public:
    MapSelectUI();
    ~MapSelectUI() = default;

    bool taiTaiNguyen();

    int xuLySuKien(const sf::Event& suKien);

    void capNhat(const sf::Vector2i& viTriChuot);
    void ve(sf::RenderWindow& cuaSo);

    int layMapDaChon() const { return banDoDaChon; }
    void datLai() { chiSoBanDoNoi = 0; banDoDaChon = -1; }
}; 
