#include "MenuUI.h"
#include <iostream>

MenuUI::MenuUI() : mucDaChon(0) {
}

bool MenuUI::taiTaiNguyen() {
    if (!ketCauNen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menutext.png")) {
        return false;
    }
    anhNen.setTexture(ketCauNen);
    ketCauNen.setSmooth(true);

    thieLapCacNut();

    return true;
}

void MenuUI::thieLapCacNut() {
    nutChoi.setSize(sf::Vector2f(270, 90));
    nutChoi.setPosition(275, 300);
    nutChoi.setFillColor(sf::Color(0, 0, 0, 0));
    nutChoi.setOutlineThickness(0);

    nutHuongDan.setSize(sf::Vector2f(270, 90));
    nutHuongDan.setPosition(275, 454);
    nutHuongDan.setFillColor(sf::Color(0, 0, 0, 0));
    nutHuongDan.setOutlineThickness(0);

    nutThoat.setSize(sf::Vector2f(270, 90));
    nutThoat.setPosition(275, 610);
    nutThoat.setFillColor(sf::Color(0, 0, 0, 0));
    nutThoat.setOutlineThickness(0);
}

bool MenuUI::chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot) {
    sf::FloatRect gioiHanNut = nut.getGlobalBounds();
    return gioiHanNut.contains(static_cast<float>(viTriChuot.x),
        static_cast<float>(viTriChuot.y));
}

MenuAction MenuUI::xuLySuKien(const sf::Event& suKien) {
    if (suKien.type == sf::Event::MouseButtonPressed &&
        suKien.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

        if (chuotDeLenNut(nutChoi, viTriChuot)) {
            return MenuAction::CHOI;
        }
        if (chuotDeLenNut(nutHuongDan, viTriChuot)) {
            return MenuAction::HUONG_DAN;
        }
        if (chuotDeLenNut(nutThoat, viTriChuot)) {
            return MenuAction::THOAT;
        }
    }

    if (suKien.type == sf::Event::KeyPressed) {
        switch (suKien.key.code) {
        case sf::Keyboard::Up:
            mucDaChon = (mucDaChon - 1 + 3) % 3;
            break;
        case sf::Keyboard::Down:
            mucDaChon = (mucDaChon + 1) % 3;
            break;
        case sf::Keyboard::Enter:
            if (mucDaChon == 0) return MenuAction::CHOI;
            if (mucDaChon == 1) return MenuAction::HUONG_DAN;
            return MenuAction::THOAT;
        case sf::Keyboard::Escape:
            return MenuAction::THOAT;
        }
    }

    if (suKien.type == sf::Event::MouseMoved) {
        sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

        if (chuotDeLenNut(nutChoi, viTriChuot)) {
            mucDaChon = 0;
        }
        else if (chuotDeLenNut(nutHuongDan, viTriChuot)) {
            mucDaChon = 1;
        }
        else if (chuotDeLenNut(nutThoat, viTriChuot)) {
            mucDaChon = 2;
        }
    }

    return MenuAction::KHONG;
}

void MenuUI::capNhat() {
    nutChoi.setFillColor(sf::Color(0, 0, 0, 0));
    nutHuongDan.setFillColor(sf::Color(0, 0, 0, 0));
    nutThoat.setFillColor(sf::Color(0, 0, 0, 0));

    if (mucDaChon == 0) {
        nutChoi.setFillColor(sf::Color(255, 255, 255, 50));
    }
    else if (mucDaChon == 1) {
        nutHuongDan.setFillColor(sf::Color(255, 255, 255, 50));
    }
    else {
        nutThoat.setFillColor(sf::Color(255, 255, 255, 50));
    }
}

void MenuUI::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(anhNen);
    cuaSo.draw(nutChoi);
    cuaSo.draw(nutHuongDan);
    cuaSo.draw(nutThoat);
}