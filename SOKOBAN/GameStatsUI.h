#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameStatsUI {
private:
    sf::Clock dongHoGame;
    float thoiGianChoi;
    bool dangChay;
    int soBuocDi;
    
    sf::Font chuPhong;
    sf::Text textThoiGian;
    sf::Text textSoBuoc;
    sf::Texture ketCauKhungTimer;
    sf::Sprite spriteKhungTimer;
    sf::Texture ketCauKhungSteps;
    sf::Sprite spriteKhungSteps;
    
public:
    GameStatsUI();

    bool khoiTao(const std::string& duongDanKhungTimer, 
                 const std::string& duongDanKhungSteps);

    void batDauTimer();
    void tamDungTimer();
    void tiepTucTimer();
    void datLaiTimer();
    float layThoiGian() const;
    void tangSoBuoc();
    void datLaiSoBuoc();
    void datSoBuoc(int soBuoc);
    int laySoBuoc() const;
    
    void capNhat();
    void ve(sf::RenderWindow& cuaSo);
    
private:
    std::string dinhDangThoiGian(float giay) const;
};