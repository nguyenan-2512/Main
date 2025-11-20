#pragma once
#include "Diem.h"
#include "HoatHinhDoiTuong.h"  // ✅ THÊM dòng này
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

    // ✅ THÊM: Biến quản lý animation
    HoatHinhDoiTuong* hoatHinh;
    bool coHoatHinh;

public:
    DoiTuongTroChoi(int x, int y, int kichThuocO);
    virtual ~DoiTuongTroChoi();  // ✅ Thêm virtual destructor

    // Getter
    Diem layViTri() const;
    int layX() const;
    int layY() const;

    // Setter
    void datViTri(int x, int y);
    void datKetCau(const sf::Texture& ketCau);

    // ✅ THÊM: Các hàm quản lý animation
    void datHoatHinh(const std::string& duongDanTexture,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh,
        float tocDoHoatHinh = 0.1f,
        bool lapLai = true);

    void capNhatHoatHinh(float thoiGianDelta);  // ✅ THÊM dòng này

    bool coAnimation() const { return coHoatHinh; }

    // Phương thức nhận dạng (phải override ở class con)
    virtual LoaiDoiTuong layLoai() const = 0;

    // Kiểm tra có phải vật cản không (mặc định = false)
    virtual bool laVatCanDiChuyen() const { return false; }

    // Phương thức vẽ (phải override ở class con)
    virtual void ve(sf::RenderWindow& cuaSo) = 0;
};