#pragma once
#include "DoiTuongTroChoi.h"

class ViTriDat : public DoiTuongTroChoi {
public:
    ViTriDat();
    ViTriDat(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};