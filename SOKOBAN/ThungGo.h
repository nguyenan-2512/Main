#pragma once
#include "DoiTuongTroChoi.h"

class ThungGo : public DoiTuongTroChoi {
private:
    bool dangTrenViTriDat;  // Thùng có đang trên vị trí đặt không
    const sf::Texture* ketCauBinhThuong;
    const sf::Texture* ketCauTrenViTriDat;

public:
    ThungGo();
    ThungGo(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;

    void datTrangThaiTrenViTriDat(bool trenViTriDat);
    bool layTrangThaiTrenViTriDat() const;

    void datKetCauBinhThuong(const sf::Texture& ketCau);
    void datKetCauTrenViTriDat(const sf::Texture& ketCau);
    void capNhatKetCau();
};