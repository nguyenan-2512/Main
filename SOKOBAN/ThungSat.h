#pragma once
#include "DoiTuongTroChoi.h"
#include <SFML/Graphics.hpp>

class ThungSat : public DoiTuongTroChoi {
private:
    const sf::Texture* ketCau;

public:
    ThungSat();
    ThungSat(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::THUNG_SAT;
    }

    bool laVatCanDiChuyen() const override {
        return true;  // Thùng sắt chặn đường
    }

    void ve(sf::RenderWindow& cuaSo) override;
    void datKetCauThungSat(const sf::Texture& ketCau);
};