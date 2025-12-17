// File: WinUI.cpp
#include "WinUI.h"
#include <sstream>
#include <iomanip>
#include <iostream>

WinUI::WinUI() : soSaoHienTai(1), thoiGianWin(0.0f), soBuocWin(0) {
}

bool WinUI::khoiTao(
    const std::string& duongDan3Sao,
    const std::string& duongDan2Sao,
    const std::string& duongDan1Sao) {

    // ===== LOAD 3 ẢNH =====
    if (!ketCau3Sao.loadFromFile(duongDan3Sao)) {
        std::cerr << "[WinUI] Khong the tai anh 3 sao!" << std::endl;
        return false;
    }

    if (!ketCau2Sao.loadFromFile(duongDan2Sao)) {
        std::cerr << "[WinUI] Khong the tai anh 2 sao!" << std::endl;
        return false;
    }

    if (!ketCau1Sao.loadFromFile(duongDan1Sao)) {
        std::cerr << "[WinUI] Khong the tai anh 1 sao!" << std::endl;
        return false;
    }

    // ===== VỊ TRÍ ẢNH WIN (GIỮA MÀN HÌNH) =====
    anhWinHienTai.setTexture(ketCau3Sao);
    // TODO: BẠN ĐIỀU CHỈNH VỊ TRÍ CHO ĐÚNG
    anhWinHienTai.setPosition(90.0f, 90.0f);

    // ===== LOAD FONT =====
    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        std::cerr << "[WinUI] Khong the tai font!" << std::endl;
        return false;
    }

    // ===== THIẾT LẬP TEXT THỜI GIAN =====
    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(24);  // TODO:  CHỈNH CỠ CHỮ
    textThoiGian.setFillColor(sf::Color::Black);  // TODO: CHỈNH MÀU CHỮ
    textThoiGian.setStyle(sf::Text::Bold);
    // TODO: CHỈNH VỊ TRÍ BÊN PHẢI ICON ĐỒNG HỒ
    textThoiGian.setPosition(337.0f, 405.0f);

    // ===== THIẾT LẬP TEXT SỐ BƯỚC =====
    textSoBuoc.setFont(chuPhong);
    textSoBuoc.setCharacterSize(24);  // TODO: CHỈNH CỠ CHỮ
    textSoBuoc.setFillColor(sf::Color::Black);  // TODO: CHỈNH MÀU CHỮ
    textSoBuoc.setStyle(sf::Text::Bold);
    // TODO: CHỈNH VỊ TRÍ BÊN PHẢI ICON CHÂN
    textSoBuoc.setPosition(456.0f, 405.0f);

    // ===== VỊ TRÍ CÁC NÚT (DỰA VÀO ẢNH CỦA BẠN) =====
    // TODO: BẠN ĐO TỌA ĐỘ CHÍNH XÁC TỪ ẢNH
    vungClickHome = sf::FloatRect(
        271.0f,   // X (trái)
        497.0f,   // Y (trên)
        117.0f,   // Chiều rộng
        26.0f     // Chiều cao
    );

    vungClickNext = sf::FloatRect(
        401.0f,   // X
        497.0f,   // Y
        117.0f,   // Chiều rộng
        26.0f     // Chiều cao
    );

    std::cout << "[WinUI] Khoi tao thanh cong!" << std::endl;
    return true;
}

int WinUI::tinhSoSao(float thoiGian, int soBuoc) {
    // ===== TODO: BẠN ĐIỀU CHỈNH ĐIỀU KIỆN ĐẠT SAO =====
    // Ví dụ đơn giản: 

    // 3 SAO:  Thời gian <= 60s VÀ số bước <= 100
    if (thoiGian <= 60.0f && soBuoc <= 100) {
        return 3;
    }

    // 2 SAO:  Thời gian <= 120s VÀ số bước <= 200
    if (thoiGian <= 120.0f && soBuoc <= 200) {
        return 2;
    }

    // 1 SAO: Các trường hợp còn lại
    return 1;
}

void WinUI::hienThi(float thoiGian, int soBuoc) {
    thoiGianWin = thoiGian;
    soBuocWin = soBuoc;

    // ===== TÍNH SỐ SAO =====
    soSaoHienTai = tinhSoSao(thoiGian, soBuoc);

    // ===== CHỌN ẢNH TƯƠNG ỨNG =====
    if (soSaoHienTai == 3) {
        anhWinHienTai.setTexture(ketCau3Sao);
        std::cout << "[WinUI] Hien thi 3 sao (Smart Solver)!" << std::endl;
    }
    else if (soSaoHienTai == 2) {
        anhWinHienTai.setTexture(ketCau2Sao);
        std::cout << "[WinUI] Hien thi 2 sao (Good Solver)!" << std::endl;
    }
    else {
        anhWinHienTai.setTexture(ketCau1Sao);
        std::cout << "[WinUI] Hien thi 1 sao (Beginner)!" << std::endl;
    }

    // ===== CẬP NHẬT TEXT =====
    textThoiGian.setString(dinhDangThoiGian(thoiGian));
    textSoBuoc.setString(std::to_string(soBuoc));
}

WinUI::HanhDongWin WinUI::kiemTraClick(const sf::Vector2i& viTriChuot) {
    sf::Vector2f viTriFloat(static_cast<float>(viTriChuot.x),
        static_cast<float>(viTriChuot.y));

    if (vungClickHome.contains(viTriFloat)) {
        std::cout << "[WinUI] Click nut HOME!" << std::endl;
        return HanhDongWin::HOME;
    }

    if (vungClickNext.contains(viTriFloat)) {
        std::cout << "[WinUI] Click nut NEXT!" << std::endl;
        return HanhDongWin::NEXT;
    }

    return HanhDongWin::KHONG;
}

void WinUI::ve(sf::RenderWindow& cuaSo) {
    // ===== VẼ NỀN ĐEN MỜ =====
    sf::RectangleShape lopPhu(sf::Vector2f(800, 800));
    lopPhu.setFillColor(sf::Color(0, 0, 0, 150));
    cuaSo.draw(lopPhu);

    // ===== VẼ ẢNH WIN =====
    cuaSo.draw(anhWinHienTai);

    // ===== VẼ TEXT =====
    cuaSo.draw(textThoiGian);
    cuaSo.draw(textSoBuoc);
}

std::string WinUI::dinhDangThoiGian(float giay) const {
    int phut = static_cast<int>(giay) / 60;
    int giayConLai = static_cast<int>(giay) % 60;

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << phut << ":"
        << std::setfill('0') << std::setw(2) << giayConLai;
    return oss.str();
}