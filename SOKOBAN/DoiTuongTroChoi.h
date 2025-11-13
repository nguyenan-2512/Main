// DoiTuongTroChoi.h - Lớp cha cho tất cả các đối tượng trong game
#pragma once
#include "Diem.h"
#include <SFML/Graphics.hpp>

class DoiTuongTroChoi {
protected:
    Diem viTri;
    sf::Sprite sprite;
    int kichThuocO;

public:
    DoiTuongTroChoi(int x, int y, int kichThuocO);
    virtual ~DoiTuongTroChoi() = default;

    // Getter
    Diem layViTri() const;
    int layX() const;
    int layY() const;

    // Setter
    void datViTri(int x, int y);
    void datKetCau(const sf::Texture& ketCau);

    // Phương thức vẽ (phải override ở class con)
    virtual void ve(sf::RenderWindow& cuaSo) = 0;
};