#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class HuongDan {
private:
    DynamicArray<sf::Texture*> cacKetCauTrang; 
    DynamicArray<sf::Sprite> cacAnhTrang;       

    bool quayLaiThucDon;  
    int trangHienTai;    
    int tongSoTrang;      

    sf::CircleShape nutTruoc;  
    sf::CircleShape nutSau;    

public:
    HuongDan();
    bool taiTaiNguyen();  
    void xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo);
    void capNhat(float thoiGianDelta);
    void ve(sf::RenderWindow& cuaSo);
    void datLai();
    bool nenQuayLaiThucDon() const { return quayLaiThucDon; }
    void datLaiCoQuayLai() { quayLaiThucDon = false; }
    bool chuotDeLenNut(const sf::CircleShape& nut, sf::Vector2i viTriChuot);
};