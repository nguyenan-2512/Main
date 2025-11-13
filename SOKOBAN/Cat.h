#pragma once
#include "DoiTuongTroChoi.h"

class Cat : public DoiTuongTroChoi {
public:
    Cat();
    Cat(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
};