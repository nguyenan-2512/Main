
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WinUI {
private:
    // ===== CÁC ẢNH WIN (3 loại) =====
    sf::Texture ketCau3Sao;   // Ảnh win 3 sao (Smart Solver)
    sf::Texture ketCau2Sao;   // Ảnh win 2 sao (Good Solver)
    sf::Texture ketCau1Sao;   // Ảnh win 1 sao (Beginner)

    sf::Sprite anhWinHienTai;

    // ===== TEXT HIỂN THỊ =====
    sf::Font chuPhong;
    sf::Text textThoiGian;   // Hiển thị thời gian (bên trái icon đồng hồ)
    sf::Text textSoBuoc;     // Hiển thị số bước (bên phải icon chân)

    // ===== VÙNG CLICK CHO NÚT =====
    sf::FloatRect vungClickHome;
    sf::FloatRect vungClickNext;

    // ===== DATA =====
    int soSaoHienTai;  // 1, 2, hoặc 3
    float thoiGianWin;
    int soBuocWin;

public:
    WinUI();

    // Khởi tạo (load 3 ảnh)
    bool khoiTao(
        const std::string& duongDan3Sao,
        const std::string& duongDan2Sao,
        const std::string& duongDan1Sao
    );

    // Tính số sao dựa trên thời gian và số bước
    // TODO: BẠN TỰ ĐIỀU CHỈNH ĐIỀU KIỆN ĐẠT SAO
    int tinhSoSao(float thoiGian, int soBuoc);

    // Hiển thị màn hình win với thông tin
    void hienThi(float thoiGian, int soBuoc);

    // Kiểm tra click vào nút
    enum class HanhDongWin { KHONG, HOME, NEXT };
    HanhDongWin kiemTraClick(const sf::Vector2i& viTriChuot);

    // Vẽ
    void ve(sf::RenderWindow& cuaSo);

private:
    std::string dinhDangThoiGian(float giay) const;
};