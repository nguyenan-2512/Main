// File: LopPhuPause.h (SỬA LẠI - GIỮ ẢNH MENU)
#pragma once
#include <SFML/Graphics.hpp>
#include "NutUI.h"
#include <iostream>

enum class HanhDongPause {
    KHONG,
    TIEP_TUC,
    CHOI_LAI,
    THOAT
};

class LopPhuPause {
private:
    sf::RectangleShape lopPhu;  // Nền đen mờ phía sau

    // ✅ GIỮ LẠI: Ảnh khung menu pause
    sf::Texture ketCauMenuPause;
    sf::Sprite anhMenuPause;

    NutUI nutTiepTuc;
    NutUI nutChoiLai;
    NutUI nutThoat;
    bool dangHienThi;

public:
    LopPhuPause() : dangHienThi(false) {
        // Nền đen mờ toàn màn hình
        lopPhu.setSize(sf::Vector2f(800, 800));
        lopPhu.setFillColor(sf::Color(0, 0, 0, 150)); // Mờ nhẹ để thấy menu
        lopPhu.setPosition(0, 0);
    }

    bool khoiTao(const std::string& duongDanAnhMenuPause) {
        // ✅ Load ảnh khung menu pause
        if (!ketCauMenuPause.loadFromFile(duongDanAnhMenuPause)) {
            std::cerr << "Khong the tai anh menu pause: " << duongDanAnhMenuPause << std::endl;
            return false;
        }

        anhMenuPause.setTexture(ketCauMenuPause);
        anhMenuPause.setPosition(90.0f, 90.0f);
        anhMenuPause.setScale(
            600.0f / ketCauMenuPause.getSize().x,
            680.0f / ketCauMenuPause.getSize().y
        );

        // Load các nút bấm
        if (!nutTiepTuc.taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\resume_button.png")) {
            std::cerr << "Khong the tai nut Tiep Tuc!" << std::endl;
            return false;
        }
        nutTiepTuc.datViTri(260.0f, 180.0f);
        nutTiepTuc.datKichThuoc(240.0f, 176.0f);

        if (!nutChoiLai.taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\restart_button.png")) {
            std::cerr << "Khong the tai nut Choi Lai!" << std::endl;
            return false;
        }
        nutChoiLai.datViTri(260.0f, 280.0f);
        nutChoiLai.datKichThuoc(245.0f, 176.0f);

        if (!nutThoat.taiAnh("D:\\PBL2\\SOKOBAN2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\exit_button.png")) {
            std::cerr << "Khong the tai nut Thoat!" << std::endl;
            return false;
        }
        nutThoat.datViTri(260.0f, 380.0f);
        nutThoat.datKichThuoc(240.0f, 176.0f);

        std::cout << "Da khoi tao Pause Menu thanh cong!" << std::endl;
        return true;
    }

    void hienThi() { dangHienThi = true; }
    void an() { dangHienThi = false; }
    bool coDangHienThi() const { return dangHienThi; }

    HanhDongPause kiemTraClick(const sf::Vector2i& viTriChuot) {
        if (!dangHienThi) return HanhDongPause::KHONG;

        if (nutTiepTuc.kiemTraClick(viTriChuot)) {
            std::cout << "Click nut Tiep Tuc!" << std::endl;
            return HanhDongPause::TIEP_TUC;
        }
        if (nutChoiLai.kiemTraClick(viTriChuot)) {
            std::cout << "Click nut Choi Lai!" << std::endl;
            return HanhDongPause::CHOI_LAI;
        }
        if (nutThoat.kiemTraClick(viTriChuot)) {
            std::cout << "Click nut Thoat!" << std::endl;
            return HanhDongPause::THOAT;
        }

        return HanhDongPause::KHONG;
    }

    void capNhat(const sf::Vector2i& viTriChuot) {
        if (!dangHienThi) return;
        nutTiepTuc.capNhat(viTriChuot);
        nutChoiLai.capNhat(viTriChuot);
        nutThoat.capNhat(viTriChuot);
    }

    void ve(sf::RenderWindow& cuaSo) {
        if (!dangHienThi) return;

        cuaSo.draw(lopPhu);          // 1. Vẽ nền đen mờ
        cuaSo.draw(anhMenuPause);    // 2. Vẽ khung menu pause
        nutTiepTuc.ve(cuaSo);        // 3. Vẽ nút Tiếp tục
        nutChoiLai.ve(cuaSo);        // 4. Vẽ nút Chơi lại
        nutThoat.ve(cuaSo);          // 5. Vẽ nút Thoát
    }
};