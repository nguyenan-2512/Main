#pragma once
#include "DoiTuongTroChoi.h"

class VatCan : public DoiTuongTroChoi {
public:
    VatCan();  
    VatCan(int x, int y, int kichThuocO);

    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::VAT_CAN;
    }

    bool laVatCanDiChuyen() const override {
        return true;  
    }

    void ve(sf::RenderWindow& cuaSo) override;
};