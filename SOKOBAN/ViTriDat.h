#pragma once
#include "DoiTuongTroChoi.h"

class ViTriDat : public DoiTuongTroChoi {
public:
    ViTriDat();  // ✅ THÊM constructor mặc định
    ViTriDat(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::VI_TRI_DAT;
    }

    // Vị trí đặt KHÔNG chặn đường

    void ve(sf::RenderWindow& cuaSo) override;
};