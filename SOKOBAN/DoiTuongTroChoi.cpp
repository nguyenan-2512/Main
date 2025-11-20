#include "DoiTuongTroChoi.h"

DoiTuongTroChoi::DoiTuongTroChoi(int x, int y, int kichThuocO)
    : viTri(x, y),
    kichThuocO(kichThuocO),
    hoatHinh(nullptr),
    coHoatHinh(false) {
    sprite.setPosition(
        static_cast<float>(x * kichThuocO),
        static_cast<float>(y * kichThuocO)
    );
}

DoiTuongTroChoi::~DoiTuongTroChoi() {
    if (hoatHinh) {
        delete hoatHinh;
        hoatHinh = nullptr;
    }
}

Diem DoiTuongTroChoi::layViTri() const {
    return viTri;
}

int DoiTuongTroChoi::layX() const {
    return viTri.layX();
}

int DoiTuongTroChoi::layY() const {
    return viTri.layY();
}

void DoiTuongTroChoi::datViTri(int x, int y) {
    viTri.datXY(x, y);
    sprite.setPosition(
        static_cast<float>(x * kichThuocO),
        static_cast<float>(y * kichThuocO)
    );
}

void DoiTuongTroChoi::datKetCau(const sf::Texture& ketCau) {
    if (!coHoatHinh) {  // Chỉ set texture nếu không có animation
        sprite.setTexture(ketCau);
    }
}

// ✅ THÊM: Thiết lập animation cho đối tượng
void DoiTuongTroChoi::datHoatHinh(const std::string& duongDanTexture,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh,
    float tocDoHoatHinh,
    bool lapLai) {
    if (hoatHinh) {
        delete hoatHinh;
    }

    hoatHinh = new HoatHinhDoiTuong();
    if (hoatHinh->khoiTao(&sprite, duongDanTexture,
        chieuRongKhung, chieuCaoKhung,
        soKhungHinh, tocDoHoatHinh, lapLai)) {
        coHoatHinh = true;
    }
    else {
        delete hoatHinh;
        hoatHinh = nullptr;
        coHoatHinh = false;
    }
}

void DoiTuongTroChoi::capNhatHoatHinh(float thoiGianDelta) {
    if (hoatHinh && coHoatHinh) {
        hoatHinh->capNhat(thoiGianDelta);
    }
}