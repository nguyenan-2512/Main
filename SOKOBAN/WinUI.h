
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WinUI {
private:

    sf::Texture ketCau3Sao;   
    sf::Texture ketCau2Sao;   
    sf::Texture ketCau1Sao;   
    sf::Sprite anhWinHienTai;
    sf::Font chuPhong;
    sf::Text textThoiGian;   
    sf::Text textSoBuoc;     
    sf::FloatRect vungClickHome;
    sf::FloatRect vungClickNext;

    int soSaoHienTai;
    float thoiGianWin;
    int soBuocWin;

public:
    WinUI();
    bool khoiTao(
        const std::string& duongDan3Sao,
        const std::string& duongDan2Sao,
        const std::string& duongDan1Sao
    );
    int tinhSoSao(float thoiGian, int soBuoc);
    void hienThi(float thoiGian, int soBuoc);
    enum class HanhDongWin { KHONG, HOME, NEXT };
    HanhDongWin kiemTraClick(const sf::Vector2i& viTriChuot);
    void ve(sf::RenderWindow& cuaSo);
private:
    std::string dinhDangThoiGian(float giay) const;
};