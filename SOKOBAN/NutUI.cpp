#include "NutUI.h"
#include <iostream>

NutUI::NutUI() : dangHover(false), dangHienThi(true) {
}

NutUI::~NutUI() {
}

bool NutUI::taiAnh(const std::string& duongDanAnh) {
    if (!ketCau.loadFromFile(duongDanAnh)) {
        return false;
    }
    anhSprite.setTexture(ketCau);
    vungClick = anhSprite.getGlobalBounds();
    return true;
}

void NutUI::datViTri(float x, float y) {
    anhSprite.setPosition(x, y);
    vungClick = anhSprite.getGlobalBounds();
}

void NutUI::datKichThuoc(float rong, float cao) {
    if (ketCau.getSize().x == 0 || ketCau.getSize().y == 0) {
        return;
    }
    
    float tyLeX = rong / ketCau.getSize().x;
    float tyLeY = cao / ketCau.getSize().y;
    anhSprite.setScale(tyLeX, tyLeY);
    
    vungClick = anhSprite.getGlobalBounds();
}

bool NutUI::kiemTraClick(const sf::Vector2i& viTriChuot) const {
    if (!dangHienThi) return false;
    
    return vungClick.contains(static_cast<float>(viTriChuot.x), 
                             static_cast<float>(viTriChuot.y));
}

bool NutUI::kiemTraHover(const sf::Vector2i& viTriChuot) const {
    if (!dangHienThi) return false;
    
    return vungClick.contains(static_cast<float>(viTriChuot.x), 
                             static_cast<float>(viTriChuot.y));
}

void NutUI::capNhat(const sf::Vector2i& viTriChuot) {
    if (!dangHienThi) {
        dangHover = false;
        return;
    }
    
    dangHover = kiemTraHover(viTriChuot);
    
    if (dangHover) {
        anhSprite.setColor(sf::Color(255, 255, 255, 255));
    } else {
        anhSprite.setColor(sf::Color(255, 255, 255, 220)); 
    }
}

void NutUI::ve(sf::RenderWindow& cuaSo) {
    if (dangHienThi) {
        cuaSo.draw(anhSprite);
    }
}