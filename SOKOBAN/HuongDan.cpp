#include "HuongDan.h"
#include <iostream>

HuongDan::HuongDan()
    : trangHienTai(0), tongSoTrang(0)
{
    quayLaiThucDon = false;

    nutTruoc.setRadius(37.f);
    nutTruoc.setOrigin(37.f, 37.f);
    nutTruoc.setPosition(77.f, 63.f);
    nutTruoc.setFillColor(sf::Color(255, 255, 0, 80));  
    nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 255)); 
    nutTruoc.setOutlineThickness(3.f);

    nutSau.setRadius(35.f);
    nutSau.setOrigin(35.f, 35.f);
    nutSau.setPosition(713.f, 58.f);
    nutSau.setFillColor(sf::Color(255, 255, 0, 80));
    nutSau.setOutlineColor(sf::Color(255, 255, 0, 255));
    nutSau.setOutlineThickness(3.f);
}

bool HuongDan::taiTaiNguyen() {
    cacKetCauTrang.clear();
    cacAnhTrang.clear();
    tongSoTrang = 0;

    DynamicArray<std::string> cacSlide;
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide1.5.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide2.11.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide3.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide4.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide5.1.png");
    cacSlide.push_back("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\slide6.1.png");

    for (int i = 0; i < cacSlide.size(); ++i) {
        sf::Texture* ketCau = new sf::Texture();
        if (!ketCau->loadFromFile(cacSlide[i])) {
            delete ketCau;
            continue;
        }

        cacKetCauTrang.push_back(ketCau);

        sf::Sprite sprite;
        sprite.setTexture(*ketCau);
        sprite.setPosition(0.f, 0.f);
        cacAnhTrang.push_back(sprite);
    }

    tongSoTrang = cacAnhTrang.size();

    if (tongSoTrang == 0) {
        return false;
    }
    return true;
}

void HuongDan::datLai() {
    trangHienTai = 0;
}

bool HuongDan::chuotDeLenNut(const sf::CircleShape& nut, sf::Vector2i viTriChuot) {
    sf::Vector2f viTriNut = nut.getPosition();
    float dx = viTriChuot.x - viTriNut.x;
    float dy = viTriChuot.y - viTriNut.y;
    return (dx * dx + dy * dy <= nut.getRadius() * nut.getRadius());
}

void HuongDan::xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo) {
    if (suKien.type == sf::Event::MouseButtonPressed &&
        suKien.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

        if (chuotDeLenNut(nutTruoc, viTriChuot)) {
            if (trangHienTai == 0) {
                quayLaiThucDon = true;
            }
            else {
                trangHienTai--;
            }
        }

        if (chuotDeLenNut(nutSau, viTriChuot) && trangHienTai < tongSoTrang - 1) {
            trangHienTai++;
        }
    }

    if (suKien.type == sf::Event::MouseMoved) {
        sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

        if (chuotDeLenNut(nutTruoc, viTriChuot)) {
            if (trangHienTai == 0) {
                nutTruoc.setOutlineColor(sf::Color(255, 120, 120, 255));
                nutTruoc.setFillColor(sf::Color(255, 0, 0, 160));
            }
            else {
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 255));
            }
        }
        else {
            if (trangHienTai == 0) {
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 80));
                nutTruoc.setFillColor(sf::Color(255, 255, 0, 80));
            }
            else {
                nutTruoc.setOutlineColor(sf::Color(255, 255, 0, 80));
            }
        }

        if (chuotDeLenNut(nutSau, viTriChuot)) {
            nutSau.setOutlineColor(sf::Color(255, 255, 0, 255));
        }
        else {
            nutSau.setOutlineColor(sf::Color(255, 255, 0, 0));
        }
    }
}

void HuongDan::capNhat(float thoiGianDelta) {
}

void HuongDan::ve(sf::RenderWindow& cuaSo) {
    if (tongSoTrang == 0) return;

    cuaSo.draw(cacAnhTrang[trangHienTai]);
    cuaSo.draw(nutTruoc);
    if (trangHienTai < tongSoTrang - 1) {
        cuaSo.draw(nutSau);
    }
}