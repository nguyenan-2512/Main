#pragma once
#include "DoiTuongTroChoi.h"
#include <SFML/Graphics.hpp>

class ThungGo : public DoiTuongTroChoi {
private:
    bool dangTrenViTriDat;
    const sf::Texture* ketCauBinhThuong;
    const sf::Texture* ketCauTrenViTriDat;

    void capNhatKetCau();

public:
    ThungGo();
    ThungGo(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::THUNG_GO;
    }

    bool laVatCanDiChuyen() const override {
        return true;
    }

    void ve(sf::RenderWindow& cuaSo) override;
    void datKetCauBinhThuong(const sf::Texture& ketCau);
    void datKetCauTrenViTriDat(const sf::Texture& ketCau);
    void datTrangThaiTrenViTriDat(bool trangThai);

    // ❌ XÓA INLINE: bool layTrangThaiTrenViTriDat() const { return dangTrenViTriDat; }
    // ✅ THAY BẰNG: Chỉ khai báo
    bool layTrangThaiTrenViTriDat() const;
};