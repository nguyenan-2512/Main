#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class NutUI {
private:
    sf::Texture ketCau;
    sf::Sprite anhSprite;
    sf::FloatRect vungClick;
    bool dangHover;
    bool dangHienThi;

public:
    NutUI();
    ~NutUI();
    bool taiAnh(const std::string& duongDanAnh);
    void datViTri(float x, float y);
    void datKichThuoc(float rong, float cao);
    bool kiemTraClick(const sf::Vector2i& viTriChuot) const;
    bool kiemTraHover(const sf::Vector2i& viTriChuot) const;
    void capNhat(const sf::Vector2i& viTriChuot);
    void ve(sf::RenderWindow& cuaSo);
    void hienThi() { dangHienThi = true; }
    void an() { dangHienThi = false; }
    bool coDangHienThi() const { return dangHienThi; }
    sf::Vector2f layViTri() const { return anhSprite.getPosition(); }
    sf::FloatRect layVungClick() const { return vungClick; }
};