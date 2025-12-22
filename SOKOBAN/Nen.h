#pragma once
#include "DoiTuongTroChoi.h"

class Nen : public DoiTuongTroChoi {
public:
    Nen(); 
    Nen(int x, int y, int kichThuocO);

    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NEN;
    }
    void ve(sf::RenderWindow& cuaSo) override;
};