#pragma once
#include "DoiTuongTroChoi.h"

class Tuong : public DoiTuongTroChoi {
public:
    Tuong();  // ✅ THÊM constructor mặc định (đã có trong .cpp)
    Tuong(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::TUONG;
    }

    bool laVatCanDiChuyen() const override {
        return true;  // Tường chặn đường
    }

    void ve(sf::RenderWindow& cuaSo) override;
};