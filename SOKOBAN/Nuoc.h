#pragma once
#include "DoiTuongTroChoi.h"

class Nuoc : public DoiTuongTroChoi {
public:
    Nuoc();
    Nuoc(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};