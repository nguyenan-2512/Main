#pragma once
#include "DoiTuongTroChoi.h"
#include <SFML/Graphics.hpp>

class CongDichChuyen : public DoiTuongTroChoi {
private:
    int maSoDichChuyen;
    const sf::Texture* ketCau;

public:
    CongDichChuyen();
    CongDichChuyen(int x, int y, int kichThuocO, int maSo);

    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::CONG_DICH_CHUYEN;
    }

    void ve(sf::RenderWindow& cuaSo) override;
    void datKetCau(const sf::Texture& ketCau);
    int layMaSo() const;
};