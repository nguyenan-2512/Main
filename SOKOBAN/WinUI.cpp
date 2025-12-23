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
    if (!ketCau3Sao.loadFromFile(duongDan3Sao)) {
        return false;
    }

    if (!ketCau2Sao.loadFromFile(duongDan2Sao)) {
        return false;
    }

    if (!ketCau1Sao.loadFromFile(duongDan1Sao)) {
        return false;
    }

    anhWinHienTai.setTexture(ketCau3Sao);
    anhWinHienTai.setPosition(90.0f, 90.0f);

    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return false;
    }

    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(24); 
    textThoiGian.setFillColor(sf::Color::Black); 
    textThoiGian.setStyle(sf::Text::Bold);
    textThoiGian.setPosition(321.0f, 436.0f);

    textSoBuoc.setFont(chuPhong);
    textSoBuoc.setCharacterSize(24);  
    textSoBuoc.setFillColor(sf::Color::Black);
    textSoBuoc.setStyle(sf::Text::Bold);
    textSoBuoc.setPosition(445.0f, 436.0f);

    vungClickHome = sf::FloatRect(
        252.0f,   
        522.0f,   
        117.0f,   
        26.0f     
    );

    vungClickNext = sf::FloatRect(
        398.0f,   
        522.0f,   
        117.0f, 
        26.0f     
    );

    return true;
}

int WinUI::tinhSoSao(float thoiGian, int soBuoc) {
    if (thoiGian <= 60.0f && soBuoc <= 100) {
        return 3;
    }

    if (thoiGian <= 120.0f && soBuoc <= 150) {
        return 2;
    }

    return 1;
}

void WinUI::hienThi(float thoiGian, int soBuoc) {
    thoiGianWin = thoiGian;
    soBuocWin = soBuoc;

    soSaoHienTai = tinhSoSao(thoiGian, soBuoc);

    if (soSaoHienTai == 3) {
        anhWinHienTai.setTexture(ketCau3Sao);
    }
    else if (soSaoHienTai == 2) {
        anhWinHienTai.setTexture(ketCau2Sao);
    }
    else {
        anhWinHienTai.setTexture(ketCau1Sao);
    }

    textThoiGian.setString(dinhDangThoiGian(thoiGian));
    textSoBuoc.setString(std::to_string(soBuoc));
}

WinUI::HanhDongWin WinUI::kiemTraClick(const sf::Vector2i& viTriChuot) {
    sf::Vector2f viTriFloat(static_cast<float>(viTriChuot.x),
        static_cast<float>(viTriChuot.y));

    if (vungClickHome.contains(viTriFloat)) {
        return HanhDongWin::HOME;
    }

    if (vungClickNext.contains(viTriFloat)) {
        return HanhDongWin::NEXT;
    }

    return HanhDongWin::KHONG;
}

void WinUI::ve(sf::RenderWindow& cuaSo) {
    sf::RectangleShape lopPhu(sf::Vector2f(800, 800));
    lopPhu.setFillColor(sf::Color(0, 0, 0, 150));
    cuaSo.draw(lopPhu);
    cuaSo.draw(anhWinHienTai);
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