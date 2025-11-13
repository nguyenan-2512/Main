#pragma once
#include "DoiTuongTroChoi.h"

class Bay : public DoiTuongTroChoi {
private:
    bool dangKichHoat;  // Bẫy có đang kích hoạt không
    const sf::Texture* ketCauKichHoat;
    const sf::Texture* ketCauKhongKichHoat;

public:
    Bay();
    Bay(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;

    void datKichHoat(bool kichHoat);
    bool layTrangThaiKichHoat() const { return dangKichHoat; }

    void datKetCauKichHoat(const sf::Texture& ketCau);
    void datKetCauKhongKichHoat(const sf::Texture& ketCau);
    void capNhatKetCau();
};