#pragma once
#include "DoiTuongTroChoi.h"
#include "HoatHinh.h"
#include <SFML/Graphics.hpp>

class NguoiChoi : public DoiTuongTroChoi {
private:
    HoatHinh hoatHinh;
    int trangThaiHienTai;

    void diChuyen(int dx, int dy);

public:
    NguoiChoi(int x, int y, int kichThuocO);
    LoaiDoiTuong layLoai() const override {
        return LoaiDoiTuong::NGUOI_CHOI;
    }
    void khoiTaoHoatHinh(const sf::Texture& bangAnh,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh);
    void datViTri(int x, int y, int dx, int dy);
    void capNhat(float thoiGianDelta);
    void ve(sf::RenderWindow& cuaSo) override;
};