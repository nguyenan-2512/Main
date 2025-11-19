// DoiTuongTroChoi.h - Lớp cha cho tất cả các đối tượng trong game
#pragma once
#include "Diem.h"
#include <SFML/Graphics.hpp>

// ✅ THÊM MỚI: Enum xác định loại đối tượng
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

    // Getter
    Diem layViTri() const;
    int layX() const;
    int layY() const;

    // Setter
    void datViTri(int x, int y);
    void datKetCau(const sf::Texture& ketCau);

    // ✅ THÊM MỚI: Phương thức nhận dạng (phải override ở class con)
    virtual LoaiDoiTuong layLoai() const = 0;

    // ✅ THÊM MỚI: Kiểm tra có phải vật cản không (mặc định = false)
    virtual bool laVatCanDiChuyen() const { return false; }

    // Phương thức vẽ (phải override ở class con)
    virtual void ve(sf::RenderWindow& cuaSo) = 0;
};