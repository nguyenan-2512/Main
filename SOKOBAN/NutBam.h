#pragma once
#include "DoiTuongTroChoi.h"
#include "DynamicArray.h"  
#include "Pair.h"

class NutBam : public DoiTuongTroChoi {
private:
    bool dangDuocNhan;  // Nút có đang được nhấn không
    DynamicArray<Pair<int, int>> cacBayLienKet;  // Danh sách bẫy liên kết
    const sf::Texture* ketCauChuaNhan;
    const sf::Texture* ketCauDaNhan;

public:
    NutBam();
    NutBam(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;

    void datTrangThaiNhan(bool duocNhan);
    bool layTrangThaiNhan() const { return dangDuocNhan; }

    void themBayLienKet(int x, int y) {
        cacBayLienKet.push_back(Pair<int, int>(x, y));
    }

    const DynamicArray<Pair<int, int>>& layCacBayLienKet() const {
        return cacBayLienKet;
    }

    void datKetCauChuaNhan(const sf::Texture& ketCau);
    void datKetCauDaNhan(const sf::Texture& ketCau);
    void capNhatKetCau();
};