#pragma once
#include "DoiTuongTroChoi.h"

class VatCan : public DoiTuongTroChoi {
public:
    VatCan();
    VatCan(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};
