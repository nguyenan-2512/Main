#pragma once
#include "Diem.h"
#include <SFML/Graphics.hpp>

enum class LoaiDoiTuong {
    NEN,
    TUONG,
    THUNG_GO,
    THUNG_SAT,
    VI_TRI_DAT,
    VAT_CAN,
    NUOC,
    CAT,
    CAU,
    BAY,
    NUT_BAM,
    NGUOI_CHOI,
    CONG_DICH_CHUYEN
};

class DoiTuongTroChoi {
protected:
    Diem viTri;
    sf::Sprite sprite;
    int kichThuocO;

public:
    DoiTuongTroChoi(int x, int y, int kichThuocO);
    virtual ~DoiTuongTroChoi() = default;

    Diem layViTri() const;
    int layX() const;
    int layY() const;

    void datViTri(int x, int y);
    void datKetCau(const sf::Texture& ketCau);


    virtual LoaiDoiTuong layLoai() const = 0;
    virtual bool laVatCanDiChuyen() const { return false; }
    virtual void ve(sf::RenderWindow& cuaSo) = 0;
};