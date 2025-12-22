#pragma once
#include "DoiTuongTroChoi.h"
#include <SFML/Graphics.hpp>

class Bay : public DoiTuongTroChoi {
private:
    bool dangKichHoat;
    const sf::Texture* ketCauKichHoat;
    const sf::Texture* ketCauKhongKichHoat;
    void capNhatKetCau();

public:
    Bay();
    Bay(int x, int y, int kichThuocO);
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::BAY;
    }
    void ve(sf::RenderWindow& cuaSo) override;
    void datKichHoat(bool kichHoat);
    bool layTrangThaiKichHoat() const;
    void datKetCauKichHoat(const sf::Texture& ketCau);
    void datKetCauKhongKichHoat(const sf::Texture& ketCau);
};