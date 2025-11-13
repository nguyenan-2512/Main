#pragma once
#include "DoiTuongTroChoi.h"

class Cau : public DoiTuongTroChoi {
public:
    Cau();
    Cau(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};