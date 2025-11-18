#pragma once
#include "DoiTuongTroChoi.h"
#include <string>

class CongDichChuyen : public DoiTuongTroChoi {
private:
    int maSoDichChuyen;  // ID để nhóm các cổng với nhau (cùng ID = liên kết)
    const sf::Texture* ketCau;

public:
    CongDichChuyen();
    CongDichChuyen(int x, int y, int kichThuocO, int maSo);
    void ve(sf::RenderWindow& cuaSo) override;

    int layMaSoDichChuyen() const { return maSoDichChuyen; }
    void datMaSoDichChuyen(int maSo) { maSoDichChuyen = maSo; }
	void datKetCau(const sf::Texture& ketCau); // override lại từ class cha để thêm chức năng
};