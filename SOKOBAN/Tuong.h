// Tuong.h - Lớp đại diện cho tường
#pragma once
#include "DoiTuongTroChoi.h"

class Tuong : public DoiTuongTroChoi {
public:
    Tuong();
    Tuong(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};