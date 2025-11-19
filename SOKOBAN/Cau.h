#pragma once
#include "DoiTuongTroChoi.h"

class Cau : public DoiTuongTroChoi {
public:
    Cau();  // ✅ THÊM constructor mặc định
    Cau(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::CAU;
    }

    // Cầu KHÔNG chặn đường

    void ve(sf::RenderWindow& cuaSo) override;
};