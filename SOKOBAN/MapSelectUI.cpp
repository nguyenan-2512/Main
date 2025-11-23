#include "MapSelectUI.h"
#include <iostream>

MapSelectUI::MapSelectUI() : chiSoBanDoNoi(0), banDoDaChon(-1) {
}

bool MapSelectUI::taiTaiNguyen() {
    // Load background
    if (!ketCauNen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\selectmaptext.png")) {
        std::cerr << "[MapSelectUI] Khong the tai nen chon ban do!" << std::endl;
        return false;
    }
    anhNen.setTexture(ketCauNen);

    // Thiết lập nút quay lại
    nutQuayLai.setRadius(50.f);
    nutQuayLai.setOrigin(50.f, 50.f);
    nutQuayLai.setPosition(88.f, 711.f);
    nutQuayLai.setFillColor(sf::Color(0, 0, 0, 0));
    nutQuayLai.setOutlineThickness(0.f);

    thieLapCacNutBanDo();

    std::cout << "[MapSelectUI] Load thanh cong!" << std::endl;
    return true;
}

void MapSelectUI::thieLapCacNutBanDo() {
    cacNutBanDo.clear();

    const int soBanDo = 10;
    const float banKinhNut = 50.f;

    // Vị trí các nút map
    DynamicArray<sf::Vector2f> cacViTri;
    cacViTri.push_back(sf::Vector2f(181.f, 302.f));  // Map 1
    cacViTri.push_back(sf::Vector2f(325.f, 302.f));  // Map 2
    cacViTri.push_back(sf::Vector2f(469.f, 302.f));  // Map 3
    cacViTri.push_back(sf::Vector2f(613.f, 302.f));  // Map 4
    cacViTri.push_back(sf::Vector2f(181.f, 481.f));  // Map 5
    cacViTri.push_back(sf::Vector2f(325.f, 481.f));  // Map 6
    cacViTri.push_back(sf::Vector2f(469.f, 481.f));  // Map 7
    cacViTri.push_back(sf::Vector2f(613.f, 481.f));  // Map 8

    for (int i = 0; i < soBanDo && i < 8; ++i) {
        sf::RectangleShape nutHinhChuNhat;
        nutHinhChuNhat.setSize(sf::Vector2f(banKinhNut * 2, banKinhNut * 2));
        nutHinhChuNhat.setFillColor(sf::Color(0, 0, 0, 0));
        nutHinhChuNhat.setOutlineColor(sf::Color::Yellow);
        nutHinhChuNhat.setOutlineThickness(0.f);
        nutHinhChuNhat.setOrigin(banKinhNut, banKinhNut);
        nutHinhChuNhat.setPosition(cacViTri[i]);
        cacNutBanDo.push_back(nutHinhChuNhat);
    }
}

bool MapSelectUI::chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot) {
    sf::FloatRect gioiHanNut = nut.getGlobalBounds();
    return gioiHanNut.contains(static_cast<float>(viTriChuot.x),
        static_cast<float>(viTriChuot.y));
}

bool MapSelectUI::chuotDeLenNutTron(const sf::CircleShape& nut, sf::Vector2i viTriChuot) {
    sf::Vector2f viTri = nut.getPosition();
    float dx = viTriChuot.x - viTri.x;
    float dy = viTriChuot.y - viTri.y;
    return (dx * dx + dy * dy <= nut.getRadius() * nut.getRadius());
}

int MapSelectUI::xuLySuKien(const sf::Event& suKien) {
    // Xử lý click chuột
    if (suKien.type == sf::Event::MouseButtonPressed &&
        suKien.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

        // Click nút quay lại
        if (chuotDeLenNutTron(nutQuayLai, viTriChuot)) {
            std::cout << "[MapSelectUI] Quay lai menu chinh" << std::endl;
            return -1;
        }

        // Click chọn map
        for (int i = 0; i < cacNutBanDo.size(); ++i) {
            if (chuotDeLenNut(cacNutBanDo[i], viTriChuot)) {
                banDoDaChon = i;
                std::cout << "[MapSelectUI] Da chon Ban do: " << (i + 1) << std::endl;
                return i;
            }
        }
    }

    // Xử lý phím
    if (suKien.type == sf::Event::KeyPressed) {
        const int soBanDo = 10;

        switch (suKien.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            if (chiSoBanDoNoi % 4 > 0) {
                chiSoBanDoNoi--;
            }
            break;

        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            if (chiSoBanDoNoi % 4 < 3 && chiSoBanDoNoi < soBanDo - 1) {
                chiSoBanDoNoi++;
            }
            break;

        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            if (chiSoBanDoNoi >= 4) {
                chiSoBanDoNoi -= 4;
            }
            break;

        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            if (chiSoBanDoNoi < 4 && chiSoBanDoNoi + 4 < soBanDo) {
                chiSoBanDoNoi += 4;
            }
            break;

        case sf::Keyboard::Enter:
        case sf::Keyboard::Space:
            banDoDaChon = chiSoBanDoNoi;
            std::cout << "[MapSelectUI] Da chon Ban do: " << (banDoDaChon + 1) << std::endl;
            return chiSoBanDoNoi;

        case sf::Keyboard::Escape:
            return -1;
        }
    }

    // Xử lý hover chuột
    if (suKien.type == sf::Event::MouseMoved) {
        sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

        for (int i = 0; i < cacNutBanDo.size(); ++i) {
            if (chuotDeLenNut(cacNutBanDo[i], viTriChuot)) {
                chiSoBanDoNoi = i;
                break;
            }
        }
    }

    return -2; // Không có action
}

void MapSelectUI::capNhat(const sf::Vector2i& viTriChuot) {
    // Cập nhật hover cho nút quay lại
    if (chuotDeLenNutTron(nutQuayLai, viTriChuot)) {
        nutQuayLai.setFillColor(sf::Color(255, 255, 255, 60));
    }
    else {
        nutQuayLai.setFillColor(sf::Color(0, 0, 0, 0));
    }
}

void MapSelectUI::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(anhNen);

    // Vẽ highlight cho map đang chọn
    if (chiSoBanDoNoi >= 0 && chiSoBanDoNoi < cacNutBanDo.size()) {
        sf::Vector2f viTriNut = cacNutBanDo[chiSoBanDoNoi].getPosition();
        float banKinh = 55.f;

        for (int i = 0; i < 3; ++i) {
            sf::CircleShape vongTronNoiBat(banKinh + i * 8.f);
            vongTronNoiBat.setOrigin(banKinh + i * 8.f, banKinh + i * 8.f);
            vongTronNoiBat.setPosition(viTriNut);
            vongTronNoiBat.setFillColor(sf::Color(255, 255, 0, 50 - i * 15));
            vongTronNoiBat.setOutlineThickness(3.f - i);
            vongTronNoiBat.setOutlineColor(sf::Color(255, 255, 0, 150 - i * 40));
            cuaSo.draw(vongTronNoiBat);
        }

        sf::CircleShape vongTronChinh(banKinh);
        vongTronChinh.setOrigin(banKinh, banKinh);
        vongTronChinh.setPosition(viTriNut);
        vongTronChinh.setFillColor(sf::Color(255, 255, 100, 80));
        vongTronChinh.setOutlineThickness(4.f);
        vongTronChinh.setOutlineColor(sf::Color::Yellow);
        cuaSo.draw(vongTronChinh);
    }

    cuaSo.draw(nutQuayLai);
}