#pragma once
#include "DoiTuongTroChoi.h"

class Cat : public DoiTuongTroChoi {
public:
    Cat();  // ✅ THÊM constructor mặc định
    Cat(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::CAT;
    }

    // Cát KHÔNG chặn đường

    void ve(sf::RenderWindow& cuaSo) override;
};