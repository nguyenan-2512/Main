#pragma once
#include "DoiTuongTroChoi.h"

class Nen : public DoiTuongTroChoi {
public:
    Nen();  // ✅ THÊM constructor mặc định
    Nen(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NEN;
    }

    // Nền KHÔNG chặn đường

    void ve(sf::RenderWindow& cuaSo) override;
};