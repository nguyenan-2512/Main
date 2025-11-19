#pragma once
#include <SFML/Graphics.hpp>
#include "NutUI.h"
// #include "DynamicArray.h" // Không cần thiết nếu không dùng

// Enum để xác định hành động trong pause menu
enum class HanhDongPause {
    KHONG,
    TIEP_TUC,
    CHOI_LAI,
    // TUY_CHON đã loại bỏ
    THOAT
};

// Lớp quản lý màn hình pause - chỉ dùng ảnh
class LopPhuPause {
private:
    // Lớp phủ trong suốt (Dùng làm nền menu chính)
    sf::RectangleShape lopPhu;

    // Ảnh menu pause chính (Giữ lại nhưng KHÔNG DÙNG để vẽ ảnh nền menu)
    NutUI* anhMenuPause;

    // Các nút trong menu (3 nút)
    NutUI* nutTiepTuc;
    NutUI* nutChoiLai;
    NutUI* nutThoat;

    bool dangHienThi;

public:
    LopPhuPause();
    ~LopPhuPause();

    // Khởi tạo với đường dẫn ảnh (tham số thứ 4 sẽ bị bỏ qua)
    bool khoiTao(
        const std::string& anhMenuPause,
        const std::string& anhTiepTuc,
        const std::string& anhChoiLai,
        const std::string& anhTuyChon, // Giữ để khớp với TroChoi.cpp
        const std::string& anhThoat
    );

    // Hiện/ẩn
    void hienThi();
    void an();
    bool coDangHienThi() const { return dangHienThi; }

    // Kiểm tra click vào nút nào
    HanhDongPause kiemTraClick(const sf::Vector2i& viTriChuot);

    // Cập nhật hover
    void capNhat(const sf::Vector2i& viTriChuot);

    // Vẽ
    void ve(sf::RenderWindow& cuaSo);
};