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
    sf::RectangleShape lopPhu;  
    sf::Texture ketCauMenuPause;
    sf::Sprite anhMenuPause;
    sf::FloatRect vungClickTiepTuc;
    sf::FloatRect vungClickChoiLai;
    sf::FloatRect vungClickThoat;

    bool dangHienThi;

public:
    LopPhuPause() : dangHienThi(false) {
        lopPhu.setSize(sf::Vector2f(800,800));
        lopPhu.setFillColor(sf::Color(0, 0, 0, 150));
        lopPhu.setPosition(0, 0);
    }

    bool khoiTao(const std::string& duongDanAnhMenuPause) {
        if (!ketCauMenuPause.loadFromFile(duongDanAnhMenuPause)) {
            return false;
        }

        anhMenuPause.setTexture(ketCauMenuPause);
        anhMenuPause.setPosition(250.f, 150.0f);
        vungClickTiepTuc = sf::FloatRect(
            200.0f,   
            280.0f,   
            400.0f,   
            80.0f     
        );

        vungClickChoiLai = sf::FloatRect(
            200.0f,  
            380.0f,   
            400.0f,  
            70.0f    
        );

        vungClickThoat = sf::FloatRect(
            200.0f,  
            490.0f,   
            400.0f,   
            80.0f     
        );
        return true;
    }

    void hienThi() { dangHienThi = true; }
    void an() { dangHienThi = false; }
    bool coDangHienThi() const { return dangHienThi; }

    HanhDongPause kiemTraClick(const sf::Vector2i& viTriChuot) {
        if (!dangHienThi) return HanhDongPause::KHONG;

        sf::Vector2f viTriChuotFloat(static_cast<float>(viTriChuot.x),
            static_cast<float>(viTriChuot.y));

        if (vungClickTiepTuc.contains(viTriChuotFloat)) {
            return HanhDongPause::TIEP_TUC;
        }

        if (vungClickChoiLai.contains(viTriChuotFloat)) {
            return HanhDongPause::CHOI_LAI;
        }

        if (vungClickThoat.contains(viTriChuotFloat)) {
            return HanhDongPause::THOAT;
        }

        return HanhDongPause::KHONG;
    }

    void capNhat(const sf::Vector2i& viTriChuot) {
    }

    void ve(sf::RenderWindow& cuaSo) {
        if (!dangHienThi) return;

        cuaSo.draw(lopPhu);        
        cuaSo.draw(anhMenuPause); 
    }
};