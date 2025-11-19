#pragma once
#include "DoiTuongTroChoi.h"

class Nuoc : public DoiTuongTroChoi {
public:
    Nuoc();  // ✅ THÊM constructor mặc định
    Nuoc(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NUOC;
    }

    bool laVatCanDiChuyen() const override {
        return true;  // Nước chặn đường
    }

    void ve(sf::RenderWindow& cuaSo) override;
};