#include "GameStatsUI.h"
#include <sstream>
#include <iomanip>
#include <iostream>

GameStatsUI::GameStatsUI() 
    : thoiGianChoi(0.0f), soBuocDi(0), dangChay(false) {
}

bool GameStatsUI::khoiTao(const std::string& duongDanKhungTimer, 
                           const std::string& duongDanKhungSteps) {

    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) {
        return false;
    }
    
    if (!ketCauKhungTimer.loadFromFile(duongDanKhungTimer)) {
        return false;
    }
    spriteKhungTimer.setTexture(ketCauKhungTimer);
    
    spriteKhungTimer.setPosition(10, -7);  
    
    if (!ketCauKhungSteps.loadFromFile(duongDanKhungSteps)) {
        return false;
    }
    spriteKhungSteps.setTexture(ketCauKhungSteps);

    spriteKhungSteps.setPosition(100, -7);  

    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(18);  
    textThoiGian.setFillColor(sf::Color::Black); 
    textThoiGian.setStyle(sf::Text::Bold);
    textThoiGian.setString("00:00");
    
    textThoiGian.setPosition(54, 50);  
    
    textSoBuoc.setFont(chuPhong);
    textSoBuoc.setCharacterSize(18);  
    textSoBuoc.setFillColor(sf::Color::Black); 
    textSoBuoc.setStyle(sf::Text::Bold);
    textSoBuoc.setString("0");
    
    textSoBuoc.setPosition(180, 50);  
    return true;
}

void GameStatsUI::batDauTimer() {
    dongHoGame.restart();
    dangChay = true;
}

void GameStatsUI::tamDungTimer() {
    if (dangChay) {
        thoiGianChoi += dongHoGame.getElapsedTime().asSeconds();
        dangChay = false;
    }
}

void GameStatsUI::tiepTucTimer() {
    if (!dangChay) {
        dongHoGame.restart();
        dangChay = true;
    }
}

void GameStatsUI::datLaiTimer() {
    thoiGianChoi = 0.0f;
    dongHoGame.restart();
    dangChay = false;
}

float GameStatsUI::layThoiGian() const {
    if (dangChay) {
        return thoiGianChoi + dongHoGame.getElapsedTime().asSeconds();
    }
    return thoiGianChoi;
}

void GameStatsUI::tangSoBuoc() {
    soBuocDi++;
}

void GameStatsUI::datLaiSoBuoc() {
    soBuocDi = 0;
}

void GameStatsUI::datSoBuoc(int soBuoc) {
    soBuocDi = soBuoc;
}

int GameStatsUI::laySoBuoc() const {
    return soBuocDi;
}

void GameStatsUI::capNhat() {
    if (dangChay) {
        float thoiGianTongCong = thoiGianChoi + dongHoGame.getElapsedTime().asSeconds();
        textThoiGian.setString(dinhDangThoiGian(thoiGianTongCong));
    }
    
    textSoBuoc.setString(std::to_string(soBuocDi));
}

void GameStatsUI::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(spriteKhungTimer);
    cuaSo.draw(spriteKhungSteps);
    cuaSo.draw(textThoiGian);
    cuaSo.draw(textSoBuoc);
}

std::string GameStatsUI::dinhDangThoiGian(float giay) const {
    int phut = static_cast<int>(giay) / 60;
    int giayConLai = static_cast<int>(giay) % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << phut << ":"
        << std::setfill('0') << std::setw(2) << giayConLai;
    return oss.str();
}