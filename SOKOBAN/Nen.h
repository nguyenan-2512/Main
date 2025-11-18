#pragma once
#include "DoiTuongTroChoi.h"
#include "HoatHinh.h"

class Nen : public DoiTuongTroChoi {
private:
    HoatHinh hoatHinh;  // Sử dụng class HoatHinh có sẵn
    bool coHoatHinh;    // Có bật animation không

public:
    Nen();
    Nen(int x, int y, int kichThuocO);
    void ve(sf::RenderWindow& cuaSo) override;

    // Khởi tạo animation với sprite sheet
    void khoiTaoHoatHinh(const sf::Texture& bangAnh,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh);

    // Cập nhật animation
    void capNhat(float thoiGianDelta);

    // Bật/tắt animation
    void batHoatHinh(bool bat) { coHoatHinh = bat; }
    bool layTrangThaiHoatHinh() const { return coHoatHinh; }
};