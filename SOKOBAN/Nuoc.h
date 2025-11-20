#pragma once
#include "DoiTuongTroChoi.h"

class Nuoc : public DoiTuongTroChoi {
public:
    Nuoc();
    Nuoc(int x, int y, int kichThuocO);

    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NUOC;
    }

    bool laVatCanDiChuyen() const override {
        return true;
    }

    void ve(sf::RenderWindow& cuaSo) override;
};