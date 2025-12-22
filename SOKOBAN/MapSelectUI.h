#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class MapSelectUI {
private:
    sf::Texture ketCauNen;
    sf::Sprite anhNen;
    sf::CircleShape nutQuayLai;

    DynamicArray<sf::RectangleShape> cacNutBanDo;

    int chiSoBanDoNoi;
    int banDoDaChon;

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
    void datMapDaChon(int map) { banDoDaChon = map; chiSoBanDoNoi = map; }
    void datLai() { chiSoBanDoNoi = 0; banDoDaChon = -1; }
}; 
