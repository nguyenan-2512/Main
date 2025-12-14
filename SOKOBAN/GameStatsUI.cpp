#include "GameStatsUI.h"
#include <sstream>
#include <iomanip>
#include <iostream>

GameStatsUI::GameStatsUI() 
    : thoiGianChoi(0.0f), soBuocDi(0), dangChay(false) {
}

bool GameStatsUI::khoiTao(const std::string& duongDanKhungTimer, 
                           const std::string& duongDanKhungSteps) {
    // ===== LOAD FONT =====
    if (!chuPhong.loadFromFile("C:\\Windows\\Fonts\\cour.ttf")) {
        std::cerr << "[GameStatsUI] Loi load font!" << std::endl;
        return false;
    }
    
    // ===== LOAD TEXTURE KHUNG TIMER =====
    if (!ketCauKhungTimer.loadFromFile(duongDanKhungTimer)) {
        std::cerr << "[GameStatsUI] Loi load khung Timer!" << std::endl;
        return false;
    }
    spriteKhungTimer.setTexture(ketCauKhungTimer);
    
    // TODO: BẠN TỰ CHỈNH VỊ TRÍ KHUNG TIMER (x, y)
    spriteKhungTimer.setPosition(10, -7);  // <-- CHỈNH TẠI ĐÂY
    
    // ===== LOAD TEXTURE KHUNG STEPS =====
    if (!ketCauKhungSteps.loadFromFile(duongDanKhungSteps)) {
        std::cerr << "[GameStatsUI] Loi load khung Steps!" << std::endl;
        return false;
    }
    spriteKhungSteps.setTexture(ketCauKhungSteps);
    
    // TODO: BẠN TỰ CHỈNH VỊ TRÍ KHUNG STEPS (x, y)
    spriteKhungSteps.setPosition(100, -7);  // <-- CHỈNH TẠI ĐÂY
    
    // ===== TEXT TIMER =====
    textThoiGian.setFont(chuPhong);
    textThoiGian.setCharacterSize(18);  // <-- CHỈNH CỠ CHỮ TẠI ĐÂY
    textThoiGian.setFillColor(sf::Color::Black);  // <-- CHỈNH MÀU CHỮ TẠI ĐÂY
    textThoiGian.setStyle(sf::Text::Bold);
    textThoiGian.setString("00:00");
    
    // TODO: BẠN TỰ CHỈNH VỊ TRí TEXT TIMER (x, y)
    textThoiGian.setPosition(54, 50);  // <-- CHỈNH TẠI ĐÂY
    
    // ===== TEXT STEPS =====
    textSoBuoc.setFont(chuPhong);
    textSoBuoc.setCharacterSize(18);  // <-- CHỈNH CỠ CHỮ TẠI ĐÂY
    textSoBuoc.setFillColor(sf::Color::Black);  // <-- CHỈNH MÀU CHỮ TẠI ĐÂY
    textSoBuoc.setStyle(sf::Text::Bold);
    textSoBuoc.setString("0");
    
    // TODO: BẠN TỰ CHỈNH VỊ TRÍ TEXT STEPS (x, y)
    textSoBuoc.setPosition(180, 50);  // <-- CHỈNH TẠI ĐÂY
    
    std::cout << "[GameStatsUI] Khoi tao thanh cong!" << std::endl;
    return true;
}

// ===== TIMER METHODS =====
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

// ===== STEPS METHODS =====
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

// ===== UPDATE & RENDER =====
void GameStatsUI::capNhat() {
    // Cập nhật timer nếu đang chạy
    if (dangChay) {
        float thoiGianTongCong = thoiGianChoi + dongHoGame.getElapsedTime().asSeconds();
        textThoiGian.setString(dinhDangThoiGian(thoiGianTongCong));
    }
    
    // Cập nhật steps
    textSoBuoc.setString(std::to_string(soBuocDi));
}

void GameStatsUI::ve(sf::RenderWindow& cuaSo) {
    // Vẽ khung
    cuaSo.draw(spriteKhungTimer);
    cuaSo.draw(spriteKhungSteps);
    
    // Vẽ text
    cuaSo.draw(textThoiGian);
    cuaSo.draw(textSoBuoc);
}

// ===== HELPER =====
std::string GameStatsUI::dinhDangThoiGian(float giay) const {
    int phut = static_cast<int>(giay) / 60;
    int giayConLai = static_cast<int>(giay) % 60;
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << phut << ":"
        << std::setfill('0') << std::setw(2) << giayConLai;
    return oss.str();
}