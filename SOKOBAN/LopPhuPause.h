// File: LopPhuPause.h (MENU ĐơN GIẢN - CHỈ 1 ẢNH + TỌA ĐỘ CLICK)
#pragma once
#include <SFML/Graphics.hpp>
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

    // ✅ CHỈ CẦN 1 ẢNH DUY NHẤT (đã có bố cục sẵn: khung + nút)
    sf::Texture ketCauMenuPause;
    sf::Sprite anhMenuPause;

    // ✅ Vùng click cho từng nút (tự định nghĩa bằng tay)
    sf::FloatRect vungClickTiepTuc;
    sf::FloatRect vungClickChoiLai;
    sf::FloatRect vungClickThoat;

    bool dangHienThi;

public:
    LopPhuPause() : dangHienThi(false) {
        // Nền đen mờ toàn màn hình
        lopPhu.setSize(sf::Vector2f(800,800));
        lopPhu.setFillColor(sf::Color(0, 0, 0, 150));
        lopPhu.setPosition(0, 0);
    }

    bool khoiTao(const std::string& duongDanAnhMenuPause) {
        // ✅ Load ảnh menu pause (1 ảnh duy nhất)
        if (!ketCauMenuPause.loadFromFile(duongDanAnhMenuPause)) {
            std::cerr << "Khong the tai anh menu pause: " << duongDanAnhMenuPause << std::endl;
            return false;
        }

        anhMenuPause.setTexture(ketCauMenuPause);
        anhMenuPause.setPosition(250.f, 150.0f);

        // Nút RESUME (Tiếp tục)
        vungClickTiepTuc = sf::FloatRect(
            200.0f,   // X (trái)
            250.0f,   // Y (trên)
            400.0f,   // Chiều rộng
            80.0f     // Chiều cao
        );

        // Nút RESTART (Chơi lại)
        vungClickChoiLai = sf::FloatRect(
            200.0f,   // X
            370.0f,   // Y
            400.0f,   // Chiều rộng
            80.0f     // Chiều cao
        );

        // Nút EXIT (Thoát)
        vungClickThoat = sf::FloatRect(
            200.0f,   // X
            490.0f,   // Y
            400.0f,   // Chiều rộng
            80.0f     // Chiều cao
        );

        std::cout << "Da khoi tao Pause Menu thanh cong!" << std::endl;
        return true;
    }

    void hienThi() { dangHienThi = true; }
    void an() { dangHienThi = false; }
    bool coDangHienThi() const { return dangHienThi; }

    HanhDongPause kiemTraClick(const sf::Vector2i& viTriChuot) {
        if (!dangHienThi) return HanhDongPause::KHONG;

        sf::Vector2f viTriChuotFloat(static_cast<float>(viTriChuot.x),
            static_cast<float>(viTriChuot.y));

        // Kiểm tra click vào nút RESUME
        if (vungClickTiepTuc.contains(viTriChuotFloat)) {
            std::cout << "Click nut Tiep Tuc!" << std::endl;
            return HanhDongPause::TIEP_TUC;
        }

        // Kiểm tra click vào nút RESTART
        if (vungClickChoiLai.contains(viTriChuotFloat)) {
            std::cout << "Click nut Choi Lai!" << std::endl;
            return HanhDongPause::CHOI_LAI;
        }

        // Kiểm tra click vào nút EXIT
        if (vungClickThoat.contains(viTriChuotFloat)) {
            std::cout << "Click nut Thoat!" << std::endl;
            return HanhDongPause::THOAT;
        }

        return HanhDongPause::KHONG;
    }

    void capNhat(const sf::Vector2i& viTriChuot) {
        // Không cần cập nhật gì (không có hover effect)
    }

    void ve(sf::RenderWindow& cuaSo) {
        if (!dangHienThi) return;

        cuaSo.draw(lopPhu);          // 1. Vẽ nền đen mờ
        cuaSo.draw(anhMenuPause);    // 2. Vẽ ảnh menu pause (đã có sẵn khung + nút)
    }
};