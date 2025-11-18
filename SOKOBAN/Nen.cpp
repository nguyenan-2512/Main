#include "Nen.h"

Nen::Nen()
    : DoiTuongTroChoi(0, 0, 0),
    coHoatHinh(false) {
}

Nen::Nen(int x, int y, int kichThuocO)
    : DoiTuongTroChoi(x, y, kichThuocO),
    coHoatHinh(false) {
}

void Nen::khoiTaoHoatHinh(const sf::Texture& bangAnh,
    int chieuRongKhung,
    int chieuCaoKhung,
    int soKhungHinh) {
    // Khởi tạo HoatHinh giống như NguoiChoi
    hoatHinh = HoatHinh(&sprite, bangAnh, chieuRongKhung, chieuCaoKhung, soKhungHinh, true);
    coHoatHinh = true;
}

void Nen::capNhat(float thoiGianDelta) {
    if (coHoatHinh) {
        // Sử dụng trạng thái DI_XUONG (0) làm trạng thái mặc định cho nền
        // Vì nền không di chuyển, chỉ cần animation từ 1 hàng
        hoatHinh.capNhat(HoatHinh::DI_XUONG, thoiGianDelta);
    }
}

void Nen::ve(sf::RenderWindow& cuaSo) {
    cuaSo.draw(sprite);
}