#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

class HuongDan {
private:
    DynamicArray<sf::Texture*> cacKetCauTrang;  // Mảng texture các trang
    DynamicArray<sf::Sprite> cacAnhTrang;       // Mảng sprite hiển thị 

    bool quayLaiThucDon;  // Cờ đánh dấu cần quay lại menu
    int trangHienTai;     // Trang đang hiển thị
    int tongSoTrang;      // Tổng số trang hướng dẫn

    sf::CircleShape nutTruoc;  // Nút quay lại trang trước
    sf::CircleShape nutSau;    // Nút đi tới trang sau

public:
    HuongDan();

    bool taiTaiNguyen();  // Load các ảnh hướng dẫn
    void xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo);
    void capNhat(float thoiGianDelta);
    void ve(sf::RenderWindow& cuaSo);
    void datLai();

    bool nenQuayLaiThucDon() const { return quayLaiThucDon; }
    void datLaiCoQuayLai() { quayLaiThucDon = false; }

    bool chuotDeLenNut(const sf::CircleShape& nut, sf::Vector2i viTriChuot);
};