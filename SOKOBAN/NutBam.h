#pragma once
#include "DoiTuongTroChoi.h"
#include "DynamicArray.h"
#include <SFML/Graphics.hpp>
#include <utility>

class NutBam : public DoiTuongTroChoi {
private:
    bool dangDuocNhan;
    const sf::Texture* ketCauChuaNhan;
    const sf::Texture* ketCauDaNhan;
    DynamicArray<std::pair<int, int>> cacBayLienKet;

    void capNhatKetCau();

public:
    NutBam();
    NutBam(int x, int y, int kichThuocO);

    // ✅ THÊM MỚI
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NUT_BAM;
    }

    void ve(sf::RenderWindow& cuaSo) override;
    void datTrangThaiNhan(bool duocNhan);

    // ❌ XÓA INLINE: bool layTrangThaiNhan() const { return dangDuocNhan; }
    // ✅ THAY BẰNG:
    bool layTrangThaiNhan() const;

    void datKetCauChuaNhan(const sf::Texture& ketCau);
    void datKetCauDaNhan(const sf::Texture& ketCau);

    // ❌ XÓA INLINE: void themBayLienKet(int x, int y) { ... }
    // ✅ THAY BẰNG:
    void themBayLienKet(int x, int y);

    // ❌ XÓA INLINE: const DynamicArray<...>& layCacBayLienKet() const { ... }
    // ✅ THAY BẰNG:
    const DynamicArray<std::pair<int, int>>& layCacBayLienKet() const;
};