#pragma once
#include "DoiTuongTroChoi.h"

class ThungSat : public DoiTuongTroChoi {
private:
    const sf::Texture* ketCau;

public:
    ThungSat();
    ThungSat(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;
    void datKetCauThungSat(const sf::Texture& ketCau);
};