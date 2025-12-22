#include "GiaoDien.h"
#include <iostream>
using namespace std;

GiaoDien::GiaoDien() : mucDaChon(0), trangThaiHienTai(TrangThaiGiaoDien::MENU) {
}

GiaoDien::~GiaoDien() {
}

bool GiaoDien::taiTaiNguyen() {
    if (!ketCauNen.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\menutext.png")) {
    }
    anhNen.setTexture(ketCauNen);
    ketCauNen.setSmooth(true);

    if (!ketCauNenChonBanDo.loadFromFile("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\selectmaptext.png")) {
    }
    anhNenChonBanDo.setTexture(ketCauNenChonBanDo);

    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
    }

    thieLapCacNut();

    return true;
}

void GiaoDien::thieLapCacNut() {
    nutQuayLai.setRadius(50.f);
    nutQuayLai.setOrigin(50.f, 50.f);
    nutQuayLai.setPosition(88.f, 711.f);
    nutQuayLai.setFillColor(sf::Color(0, 0, 0, 0));
    nutQuayLai.setOutlineThickness(0.f);
    daNhanQuayLai = false;

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

void GiaoDien::xuLySuKien(const sf::Event& suKien, sf::RenderWindow& cuaSo) {

    if (trangThaiHienTai == TrangThaiGiaoDien::MENU) {
        if (suKien.type == sf::Event::MouseButtonPressed && suKien.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

            if (chuotDeLenNut(nutChoi, viTriChuot)) {
                trangThaiHienTai = TrangThaiGiaoDien::CHON_BAN_DO;
                thieLapChonBanDo(cuaSo);
            }
            else if (chuotDeLenNut(nutHuongDan, viTriChuot)) {
                trangThaiHienTai = TrangThaiGiaoDien::HUONG_DAN;
                huongDan.datLai();
                huongDan.taiTaiNguyen();
            }
            else if (chuotDeLenNut(nutThoat, viTriChuot)) {
                trangThaiHienTai = TrangThaiGiaoDien::THOAT;
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
                if (mucDaChon == 0) {
                    trangThaiHienTai = TrangThaiGiaoDien::CHON_BAN_DO;
                    thieLapChonBanDo(cuaSo);
                }
                else if (mucDaChon == 1) {
                    trangThaiHienTai = TrangThaiGiaoDien::HUONG_DAN;
                    huongDan.datLai();
                    huongDan.taiTaiNguyen();
                }
                else {
                    trangThaiHienTai = TrangThaiGiaoDien::THOAT;
                }
                break;
            case sf::Keyboard::Escape:
                trangThaiHienTai = TrangThaiGiaoDien::THOAT;
                break;
            }
        }

        if (suKien.type == sf::Event::MouseMoved) {
            sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

            if (chuotDeLenNut(nutChoi, viTriChuot)) {
                mucDaChon = 0;
                nutChoi.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                nutChoi.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (chuotDeLenNut(nutHuongDan, viTriChuot)) {
                mucDaChon = 1;
                nutHuongDan.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                nutHuongDan.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (chuotDeLenNut(nutThoat, viTriChuot)) {
                mucDaChon = 2;
                nutThoat.setFillColor(sf::Color(255, 255, 255, 50));
            }
            else {
                nutThoat.setFillColor(sf::Color(0, 0, 0, 0));
            }

            if (chuotDeLenNutTron(nutQuayLai, viTriChuot)) {
                nutQuayLai.setFillColor(sf::Color(255, 255, 255, 60));
            }
            else {
                nutQuayLai.setFillColor(sf::Color(0, 0, 0, 0));
            }
        }
    }
    else if (trangThaiHienTai == TrangThaiGiaoDien::CHON_BAN_DO) {
        if (suKien.type == sf::Event::MouseButtonPressed && suKien.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i viTriChuot(suKien.mouseButton.x, suKien.mouseButton.y);

            float dx = viTriChuot.x - nutQuayLai.getPosition().x;
            float dy = viTriChuot.y - nutQuayLai.getPosition().y;
            if (dx * dx + dy * dy <= nutQuayLai.getRadius() * nutQuayLai.getRadius()) {
                trangThaiHienTai = TrangThaiGiaoDien::MENU;
                return;
            }

            for (int i = 0; i < cacNutBanDo.getSize(); ++i) {
                if (chuotDeLenNut(cacNutBanDo[i], viTriChuot)) {
                    banDoDaChon = i;
                    trangThaiHienTai = TrangThaiGiaoDien::DANG_CHOI;
                    break;
                }
            }
        }

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
                else if (chiSoBanDoNoi >= 4 && chiSoBanDoNoi < 8) {
                    chiSoBanDoNoi = std::min(chiSoBanDoNoi + 4, soBanDo - 1);
                }
                break;

            case sf::Keyboard::Enter:
            case sf::Keyboard::Space:
                banDoDaChon = chiSoBanDoNoi;
                trangThaiHienTai = TrangThaiGiaoDien::DANG_CHOI;
                break;

            case sf::Keyboard::Escape:
                trangThaiHienTai = TrangThaiGiaoDien::MENU;
                break;
            }
        }

        if (suKien.type == sf::Event::MouseMoved) {
            sf::Vector2i viTriChuot(suKien.mouseMove.x, suKien.mouseMove.y);

            for (int i = 0; i < cacNutBanDo.getSize(); ++i) {
                if (chuotDeLenNut(cacNutBanDo[i], viTriChuot)) {
                    chiSoBanDoNoi = i;
                    break;
                }
            }
        }
    }
    else if (trangThaiHienTai == TrangThaiGiaoDien::HUONG_DAN) {
        if (huongDan.nenQuayLaiThucDon()) {
            huongDan.datLaiCoQuayLai();
            datTrangThai(TrangThaiGiaoDien::MENU);
        }
        huongDan.xuLySuKien(suKien, cuaSo);
    }
}

void GiaoDien::capNhat() {
    if (trangThaiHienTai == TrangThaiGiaoDien::MENU) {
        if (mucDaChon == 0) {
            nutChoi.setFillColor(sf::Color(255, 255, 255, 50));
            nutHuongDan.setFillColor(sf::Color(0, 0, 0, 0));
            nutThoat.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else if (mucDaChon == 1) {
            nutChoi.setFillColor(sf::Color(0, 0, 0, 0));
            nutHuongDan.setFillColor(sf::Color(255, 255, 255, 50));
            nutThoat.setFillColor(sf::Color(0, 0, 0, 0));
        }
        else {
            nutChoi.setFillColor(sf::Color(0, 0, 0, 0));
            nutHuongDan.setFillColor(sf::Color(0, 0, 0, 0));
            nutThoat.setFillColor(sf::Color(255, 255, 255, 50));
        }
    }
}

void GiaoDien::ve(sf::RenderWindow& cuaSo) {
    if (trangThaiHienTai == TrangThaiGiaoDien::MENU) {
        cuaSo.draw(anhNen);
        cuaSo.draw(nutChoi);
        cuaSo.draw(nutHuongDan);
        cuaSo.draw(nutThoat);
    }
    else if (trangThaiHienTai == TrangThaiGiaoDien::CHON_BAN_DO) {
        veManHinhChonBanDo(cuaSo);
    }
    else if (trangThaiHienTai == TrangThaiGiaoDien::HUONG_DAN) {
        huongDan.ve(cuaSo);
    }
}

TrangThaiGiaoDien GiaoDien::layTrangThai() const {
    return trangThaiHienTai;
}

void GiaoDien::datTrangThai(TrangThaiGiaoDien trangThai) {
    trangThaiHienTai = trangThai;
}

void GiaoDien::datLai() {
    trangThaiHienTai = TrangThaiGiaoDien::MENU;
    mucDaChon = 0;
}

int GiaoDien::layMapDaChon() const {
    return banDoDaChon;
}

bool GiaoDien::chuotDeLenNut(const sf::RectangleShape& nut, sf::Vector2i viTriChuot) {
    sf::FloatRect gioiHanNut = nut.getGlobalBounds();
    return gioiHanNut.contains(static_cast<float>(viTriChuot.x), static_cast<float>(viTriChuot.y));
}

bool GiaoDien::chuotDeLenNutTron(const sf::CircleShape& nut, sf::Vector2i viTriChuot) {
    sf::Vector2f viTri = nut.getPosition();
    float dx = viTriChuot.x - viTri.x;
    float dy = viTriChuot.y - viTri.y;
    return (dx * dx + dy * dy <= nut.getRadius() * nut.getRadius());
}

void GiaoDien::thieLapChonBanDo(sf::RenderWindow& cuaSo) {
    cacNutBanDo.clear();
    chiSoBanDoNoi = 0;

    const int soBanDo = 10;
    const float banKinhNut = 50.f;

    DynamicArray<sf::Vector2f> cacViTri;
    cacViTri.push_back(sf::Vector2f(181.f, 302.f)); 
    cacViTri.push_back(sf::Vector2f(325.f, 302.f));  
    cacViTri.push_back(sf::Vector2f(469.f, 302.f)); 
    cacViTri.push_back(sf::Vector2f(613.f, 302.f));  
    cacViTri.push_back(sf::Vector2f(181.f, 481.f));  
    cacViTri.push_back(sf::Vector2f(325.f, 481.f));  
    cacViTri.push_back(sf::Vector2f(469.f, 481.f));  
    cacViTri.push_back(sf::Vector2f(613.f, 481.f));  

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

void GiaoDien::veManHinhChonBanDo(sf::RenderWindow& cuaSo) {
    cuaSo.draw(anhNenChonBanDo);

    if (chiSoBanDoNoi >= 0 && chiSoBanDoNoi < cacNutBanDo.getSize()) {
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