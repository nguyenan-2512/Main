#pragma once
#include "DoiTuongTroChoi.h"
#include "HoatHinh.h"

class NguoiChoi : public DoiTuongTroChoi {
private:
    HoatHinh hoatHinh;  // Animation của nhân vật
    int trangThaiHienTai;  // Trạng thái hiện tại (hướng di chuyển)

public:
    NguoiChoi(int x = 0, int y = 0, int kichThuocO = 32);

    void ve(sf::RenderWindow& cuaSo) override;
    void capNhat(float thoiGianDelta);  // Cập nhật animation

    void khoiTaoHoatHinh(const sf::Texture& bangAnh,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh);

    void diChuyen(int dx, int dy);
    void datViTri(int x, int y, int dx, int dy);
};