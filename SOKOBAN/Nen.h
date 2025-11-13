#pragma once
#include "DoiTuongTroChoi.h"

class Nen : public DoiTuongTroChoi {
public:
    Nen();
    Nen(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};