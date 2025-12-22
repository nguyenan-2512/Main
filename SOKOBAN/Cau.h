#pragma once
#include "DoiTuongTroChoi.h"

class Cau : public DoiTuongTroChoi {
public:
    Cau();  
    Cau(int x, int y, int kichThuocO);
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::CAU;
    }
    void ve(sf::RenderWindow& cuaSo) override;
};