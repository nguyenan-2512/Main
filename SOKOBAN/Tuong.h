#pragma once
#include "DoiTuongTroChoi.h"

class Tuong : public DoiTuongTroChoi {
public:
    Tuong();  
    Tuong(int x, int y, int kichThuocO);

    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::TUONG;
    }

    bool laVatCanDiChuyen() const override {
        return true;  
    }
    void ve(sf::RenderWindow& cuaSo) override;
};