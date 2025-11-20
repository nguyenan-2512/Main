#pragma once
#include <SFML/Graphics.hpp>
#include "DynamicArray.h"

// Lớp quản lý animation cho các đối tượng tĩnh (nước, cỏ, cổng dịch chuyển...)
class HoatHinhDoiTuong {
private:
    sf::Sprite* sprite;                      // Con trỏ đến sprite cần animate
    sf::Texture bangAnh;                     // Spritesheet

    int chieuRongKhung;                      // Chiều rộng 1 frame
    int chieuCaoKhung;                       // Chiều cao 1 frame
    int soKhungHinh;                         // Tổng số frame
    int khungHienTai;                        // Frame đang hiển thị

    float tocDoHoatHinh;                     // Thời gian giữa các frame (giây)
    bool lapLai;                             // Có lặp lại không
    bool dangChay;                           // Đang chạy animation không

    sf::Clock dongHoKhung;                   // Đồng hồ đếm thời gian
    DynamicArray<sf::IntRect> cacKhung;      // Danh sách các frame

    void taoKhungHinh();                     // Tạo danh sách frame từ spritesheet

public:
    HoatHinhDoiTuong();

    // Khởi tạo animation
    HoatHinhDoiTuong(sf::Sprite* sprite,
        const sf::Texture& bangAnh,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh,
        float tocDoHoatHinh = 0.1f,
        bool lapLai = true);

    // Khởi tạo với texture path
    bool khoiTao(sf::Sprite* sprite,
        const std::string& duongDanTexture,
        int chieuRongKhung,
        int chieuCaoKhung,
        int soKhungHinh,
        float tocDoHoatHinh = 0.1f,
        bool lapLai = true);

    // Cập nhật animation
    void capNhat(float thoiGianDelta);

    // Điều khiển animation
    void batDau();
    void tamDung();
    void datLai();
    void datTocDo(float tocDo);

    // Getter
    bool dangChayAnimation() const { return dangChay; }
    int layKhungHienTai() const { return khungHienTai; }
    int laySoKhungHinh() const { return soKhungHinh; }
};