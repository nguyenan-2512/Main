#pragma once
#include "DoiTuongTroChoi.h"

class ViTriDat : public DoiTuongTroChoi {
public:
    ViTriDat();  
    ViTriDat(int x, int y, int kichThuocO);
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::VI_TRI_DAT;
    }
    void ve(sf::RenderWindow& cuaSo) override;
};