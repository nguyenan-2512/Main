#include "NguoiChoi.h"

NguoiChoi::NguoiChoi(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    trangThaiHienTai(HoatHinh::DI_XUONG) {
}

void NguoiChoi::khoiTaoHoatHinh(const sf::Texture& bangAnh,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh) {
    hoatHinh = HoatHinh(&sprite, bangAnh, chieuRongKhung, chieuCaoKhung, soKhungHinh, true);
}

void NguoiChoi::capNhat(float thoiGianDelta) {
    hoatHinh.capNhat(trangThaiHienTai, thoiGianDelta);
}

void NguoiChoi::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}

void NguoiChoi::diChuyen(int dx, int dy) {
    if (dy < 0) {
        trangThaiHienTai = HoatHinh::DI_LEN;
    }
    else if (dy > 0) {
        trangThaiHienTai = HoatHinh::DI_XUONG;
    }
    else if (dx < 0) {
        trangThaiHienTai = HoatHinh::DI_TRAI;
    }
    else if (dx > 0) {
        trangThaiHienTai = HoatHinh::DI_PHAI;
    }
}

void NguoiChoi::datViTri(int x, int y, int dx, int dy) {
    diChuyen(dx, dy);
    DoiTuongTroChoi::datViTri(x, y);
}