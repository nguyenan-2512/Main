#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameStatsUI {
private:
    // ===== TIMER LOGIC =====
    sf::Clock dongHoGame;
    float thoiGianChoi;
    bool dangChay;
    
    // ===== STEPS COUNTER =====
    int soBuocDi;
    
    // ===== UI ELEMENTS =====
    sf::Font chuPhong;
    sf::Text textThoiGian;
    sf::Text textSoBuoc;
    
    // ===== KHUNG ẢNH =====
    sf::Texture ketCauKhungTimer;
    sf::Sprite spriteKhungTimer;
    
    sf::Texture ketCauKhungSteps;
    sf::Sprite spriteKhungSteps;
    
public:
    GameStatsUI();
    
    // ===== KHỞI TẠO =====
    bool khoiTao(const std::string& duongDanKhungTimer, 
                 const std::string& duongDanKhungSteps);
    
    // ===== TIMER =====
    void batDauTimer();
    void tamDungTimer();
    void tiepTucTimer();
    void datLaiTimer();
    float layThoiGian() const;
    
    // ===== STEPS =====
    void tangSoBuoc();
    void datLaiSoBuoc();
    void datSoBuoc(int soBuoc);
    int laySoBuoc() const;
    
    // ===== UPDATE & RENDER =====
    void capNhat();
    void ve(sf::RenderWindow& cuaSo);
    
private:
    std::string dinhDangThoiGian(float giay) const;
};